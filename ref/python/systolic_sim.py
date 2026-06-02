"""Cycle-accurate simulator for the 8x8 INT8 weight-stationary systolic array.

This simulator mirrors the dataflow described in docs/spec.md. It exists for
two reasons:

  1. To validate our understanding of the dataflow BEFORE writing RTL.
     If we can't get a Python model right, we won't get RTL right.

  2. To serve as an independent cycle-aware reference for the DV environment.
     The behavioral golden (golden.py) only knows "what" the answer should be;
     this simulator knows "how" the answer is computed cycle-by-cycle.

DATAFLOW (standard weight-stationary, TPU-style):
  - A is preloaded as weights: PE(r, k) holds A[r][k].
  - B flows DOWN columns: B[k][c] enters the top of grid column k.
  - Partial sums flow RIGHT along rows, accumulating across columns.
  - C[r][c] exits the RIGHT edge of row r.

The simulator follows the three-phase operation from spec section 4:
    LOAD (8 cycles) -> COMPUTE (8 cycles) -> DRAIN (8 cycles)
"""

from __future__ import annotations

import numpy as np
from dataclasses import dataclass, field


# ---------------------------------------------------------------------------
# Constants — mirror spec.md section 2
# ---------------------------------------------------------------------------

ARRAY_SIZE = 8          # 8x8 PE grid (spec section 2: "Array size")
ACC_WIDTH = 32          # INT32 accumulator (spec section 6.1)
OPERAND_DTYPE = np.int8
ACC_DTYPE = np.int32


# ---------------------------------------------------------------------------
# PE — one processing element
# ---------------------------------------------------------------------------

@dataclass
class PE:
    """One Processing Element. Models the per-cycle behavior of a single MAC.

    Per spec section 7, each PE contains:
      - a weight register (INT8), loaded once and held stationary
      - an activation pipe register (INT8): B value, passed DOWN to the
        PE below on the next cycle
      - a psum pipe register (INT32): partial sum, passed RIGHT to the
        PE to the right on the next cycle

    Hardware analogy for the registers:
        These are flip-flops. Each cycle a flip-flop CAPTURES its input and
        DRIVES its previously captured value to neighbors. So neighbors see
        what THIS PE captured one cycle ago, not what's arriving this cycle.
        That one-cycle-per-hop delay is what makes the array "systolic".
    """

    # np.int8(0) makes the initial value an explicit INT8 zero rather than a
    # Python int — catches accidental type drift early.
    weight: np.int8 = np.int8(0)
    activation_reg: np.int8 = np.int8(0)   # flows DOWN to PE below
    psum_reg: np.int32 = np.int32(0)       # flows RIGHT to PE at right

    def load_weight(self, w) -> None:
        """Set the stationary weight register. Called once per tile, during LOAD."""
        if not (-128 <= int(w) <= 127):
            raise ValueError(f"Weight {w} out of INT8 range [-128, 127]")
        self.weight = np.int8(w)

    def tick(self, activation_in, psum_in):
        """Advance one cycle.

        Flip-flop discipline: read OLD register values (the outputs neighbors
        will see this cycle), compute NEW values from this cycle's inputs,
        write the new values, return the old ones.

        Pattern: read old -> compute new -> write new -> return old.

        Args:
            activation_in: B value arriving from the PE ABOVE this cycle
            psum_in: partial sum arriving from the PE to the LEFT this cycle

        Returns:
            (activation_out, psum_out): values this PE presents to its
            DOWN and RIGHT neighbors respectively, for the next cycle.
        """
        # Step 1: capture OLD register values — these are what neighbors see.
        activation_out = self.activation_reg   # goes DOWN
        psum_out = self.psum_reg               # goes RIGHT

        # Step 2: compute the NEW psum from this cycle's inputs.
        # Cast to INT32 before multiplying — INT8*INT8 would overflow
        # (127*127 = 16129 doesn't fit in INT8). Models the hardware's
        # sign-extension of the INT16 product into the INT32 accumulator.
        product = np.int32(self.weight) * np.int32(activation_in)
        new_psum = np.int32(psum_in) + product

        # Step 3: latch new values for next cycle.
        self.activation_reg = np.int8(activation_in)
        self.psum_reg = new_psum

        # Step 4: return what was on the output wires this cycle.
        return activation_out, psum_out

    def reset(self) -> None:
        """Clear all state. Called between tiles or on global reset."""
        self.weight = np.int8(0)
        self.activation_reg = np.int8(0)
        self.psum_reg = np.int32(0)


# ---------------------------------------------------------------------------
# SystolicArray — the 8x8 grid + the controller
# ---------------------------------------------------------------------------

@dataclass
class SystolicArray:
    """8x8 weight-stationary systolic array, cycle-accurate."""

    size: int = ARRAY_SIZE
    pes: list = field(default_factory=list)
    cycle: int = 0

    def __post_init__(self):
        """Build the PE grid after dataclass init, if not already provided."""
        if not self.pes:
            self.pes = [[PE() for _ in range(self.size)] for _ in range(self.size)]

    def reset(self) -> None:
        """Reset all PE state and the cycle counter. Called before each tile."""
        for row in self.pes:
            for pe in row:
                pe.reset()
        self.cycle = 0

    # ------------------------------------------------------------------
    # Phase 1: LOAD weights
    # ------------------------------------------------------------------

    def load_weights(self, A: np.ndarray) -> None:
        """LOAD phase: preload weights. PE(r, k) gets A[r][k].

        Real hardware shifts weights in over 8 cycles (spec section 4); for
        the simulator we assign directly — the functional result is identical.
        """
        assert A.shape == (self.size, self.size), \
            f"A shape {A.shape} != expected ({self.size}, {self.size})"
        assert A.dtype == OPERAND_DTYPE, \
            f"A dtype {A.dtype} != expected {OPERAND_DTYPE}"

        for r in range(self.size):
            for k in range(self.size):
                self.pes[r][k].load_weight(A[r, k])

        # Model LOAD taking `size` cycles so the cycle log matches the spec.
        self.cycle += self.size

    # ------------------------------------------------------------------
    # Phase 2 helper: skew the B matrix for column-wise streaming
    # ------------------------------------------------------------------

    @staticmethod
    def _skew_b_input(B: np.ndarray) -> np.ndarray:
        """Apply staircase skew to B.

        B[k][c] enters the top of grid column k at cycle (k + c). Without skew,
        all of B's first row would try to enter on cycle 0; the skew staggers
        the columns so activations meet the right partial sums at the right PEs.

        Output shape: (2*size - 1, size). skewed[t][k] is what enters the top
        of grid column k on cycle t.

        Example for 4x4:
            B =                       skewed =
            [[b00 b01 b02 b03]         [[b00  0   0   0 ]
             [b10 b11 b12 b13]          [b01 b10  0   0 ]
             [b20 b21 b22 b23]          [b02 b11 b20  0 ]
             [b30 b31 b32 b33]]         [b03 b12 b21 b30]
                                        [ 0  b13 b22 b31]
                                        [ 0   0  b23 b32]
                                        [ 0   0   0  b33]]
        """
        size = B.shape[0]
        assert B.shape == (size, size)
        assert B.dtype == OPERAND_DTYPE

        skewed = np.zeros((2 * size - 1, size), dtype=OPERAND_DTYPE)

        # B[k][c] enters grid column k at cycle (k + c).
        for k in range(size):
            for c in range(size):
                skewed[k + c, k] = B[k, c]

        return skewed

    # ------------------------------------------------------------------
    # Phase 2 + Phase 3: COMPUTE and DRAIN
    # ------------------------------------------------------------------

    def run_compute_and_drain(self, B: np.ndarray) -> np.ndarray:
        """Run COMPUTE + DRAIN. Returns the C matrix.

        B flows down columns; partial sums flow right along rows; C exits the
        right edge. We log the right-edge outputs every cycle, then unskew
        them into the final C matrix.
        """
        N = self.size

        skewed = self._skew_b_input(B)          # shape (2N-1, N)

        # Cycles needed: last B value enters at cycle 2N-2, then its row's
        # psum chain finishes N-1 hops later, plus latching. Total 3N-2.
        total_cycles = 3 * N - 2

        # right_log[t][r] = psum exiting the right edge of row r at cycle t.
        right_log = np.zeros((total_cycles, N), dtype=ACC_DTYPE)

        for c in range(total_cycles):

            # --- SNAPSHOT: freeze all PE output registers before any tick ---
            # Each PE reads its neighbors' PREVIOUS-cycle values, not values
            # already updated this cycle. This is the snapshot-then-commit
            # pattern that models a synchronous clock edge.
            snapshot = [[(self.pes[i][j].activation_reg,
                         self.pes[i][j].psum_reg)
                        for j in range(N)] for i in range(N)]

            # --- TICK every PE using snapshot values as inputs ---
            for i in range(N):
                for j in range(N):
                    # activation_in arrives from ABOVE (or the B stream if row 0)
                    if i == 0:
                        activation_in = (skewed[c, j]
                                         if c < skewed.shape[0]
                                         else np.int8(0))
                    else:
                        activation_in = snapshot[i - 1][j][0]  # act_reg above

                    # psum_in arrives from the LEFT (or 0 if leftmost column)
                    if j == 0:
                        psum_in = np.int32(0)
                    else:
                        psum_in = snapshot[i][j - 1][1]        # psum_reg left

                    self.pes[i][j].tick(activation_in, psum_in)

            # --- COLLECT right-edge outputs for this cycle ---
            for r in range(N):
                right_log[c, r] = self.pes[r][N - 1].psum_reg

            self.cycle += 1

        # --- UNSKEW: C[r][c] is finalized at row r's right edge on
        #     cycle (r + c + N - 1). ---
        C = np.zeros((N, N), dtype=ACC_DTYPE)
        for r in range(N):
            for c in range(N):
                C[r, c] = right_log[r + c + N - 1, r]

        return C

    # ------------------------------------------------------------------
    # Convenience: full tile in one call
    # ------------------------------------------------------------------

    def run_tile(self, A: np.ndarray, B: np.ndarray) -> np.ndarray:
        """Run one full tile: reset, LOAD A, then COMPUTE+DRAIN with B."""
        self.reset()
        self.load_weights(A)
        return self.run_compute_and_drain(B)