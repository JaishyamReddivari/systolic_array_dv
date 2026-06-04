"""Cycle-accurate simulator for the 8x8 INT8 weight-stationary systolic array.

See docs/spec.md section 3 for the dataflow. This module is the timing-aware
reference for the RTL: a full LOAD+COMPUTE+DRAIN sequence driven into the
hardware must reproduce run_tile() here.

DATAFLOW (standard weight-stationary, TPU-style):
  - A preloaded as weights: PE(r, k) holds A[r][k].
  - B flows DOWN columns: B[k][c] enters the top of grid column k.
  - Partial sums flow RIGHT along rows, accumulating across columns.
  - C[r][c] exits the RIGHT edge of row r.
"""

from __future__ import annotations

import numpy as np
from dataclasses import dataclass, field


ARRAY_SIZE = 8
ACC_WIDTH = 32
OPERAND_DTYPE = np.int8
ACC_DTYPE = np.int32


@dataclass
class PE:
    """One Processing Element. Counterpart of pe.sv. See that file for the
    full Python<->SystemVerilog mapping."""

    weight: np.int8 = np.int8(0)
    activation_reg: np.int8 = np.int8(0)   # flows DOWN
    psum_reg: np.int32 = np.int32(0)       # flows RIGHT

    def load_weight(self, w) -> None:
        if not (-128 <= int(w) <= 127):
            raise ValueError(f"Weight {w} out of INT8 range [-128, 127]")
        self.weight = np.int8(w)

    def tick(self, activation_in, psum_in):
        # read old -> compute new -> write new -> return old
        activation_out = self.activation_reg
        psum_out = self.psum_reg
        product = np.int32(self.weight) * np.int32(activation_in)
        new_psum = np.int32(psum_in) + product
        self.activation_reg = np.int8(activation_in)
        self.psum_reg = new_psum
        return activation_out, psum_out

    def reset(self) -> None:
        self.weight = np.int8(0)
        self.activation_reg = np.int8(0)
        self.psum_reg = np.int32(0)


@dataclass
class SystolicArray:
    """8x8 weight-stationary systolic array, cycle-accurate."""

    size: int = ARRAY_SIZE
    pes: list = field(default_factory=list)
    cycle: int = 0

    def __post_init__(self):
        if not self.pes:
            self.pes = [[PE() for _ in range(self.size)] for _ in range(self.size)]

    def reset(self) -> None:
        for row in self.pes:
            for pe in row:
                pe.reset()
        self.cycle = 0

    def load_weights(self, A: np.ndarray) -> None:
        assert A.shape == (self.size, self.size), \
            f"A shape {A.shape} != expected ({self.size}, {self.size})"
        assert A.dtype == OPERAND_DTYPE, \
            f"A dtype {A.dtype} != expected {OPERAND_DTYPE}"
        for r in range(self.size):
            for k in range(self.size):
                self.pes[r][k].load_weight(A[r, k])
        self.cycle += self.size

    @staticmethod
    def _skew_b_input(B: np.ndarray) -> np.ndarray:
        """B[k][c] enters grid column k at cycle (k + c). Output shape
        (2*size - 1, size); skewed[t][k] is what enters column k on cycle t."""
        size = B.shape[0]
        assert B.shape == (size, size)
        assert B.dtype == OPERAND_DTYPE
        skewed = np.zeros((2 * size - 1, size), dtype=OPERAND_DTYPE)
        for k in range(size):
            for c in range(size):
                skewed[k + c, k] = B[k, c]
        return skewed

    def _run_internal(self, B: np.ndarray) -> np.ndarray:
        """Run COMPUTE+DRAIN, returning the full per-cycle right-edge log.

        right_log[t][r] = psum_reg of PE(r, N-1) AFTER compute cycle t.
        This is the single source of truth; both the C matrix and the RTL
        stimulus are derived from it.
        """
        N = self.size
        skewed = self._skew_b_input(B)
        total_cycles = 3 * N - 2
        right_log = np.zeros((total_cycles, N), dtype=ACC_DTYPE)

        for c in range(total_cycles):
            # snapshot all PE output registers before any tick this cycle
            snapshot = [[(self.pes[i][j].activation_reg,
                         self.pes[i][j].psum_reg)
                        for j in range(N)] for i in range(N)]

            for i in range(N):
                for j in range(N):
                    if i == 0:
                        activation_in = (skewed[c, j]
                                         if c < skewed.shape[0]
                                         else np.int8(0))
                    else:
                        activation_in = snapshot[i - 1][j][0]
                    if j == 0:
                        psum_in = np.int32(0)
                    else:
                        psum_in = snapshot[i][j - 1][1]
                    self.pes[i][j].tick(activation_in, psum_in)

            for r in range(N):
                right_log[c, r] = self.pes[r][N - 1].psum_reg
            self.cycle += 1

        return right_log

    @staticmethod
    def _unskew(right_log: np.ndarray, N: int) -> np.ndarray:
        """C[r][c] is finalized at row r's right edge on cycle r + c + N - 1."""
        C = np.zeros((N, N), dtype=ACC_DTYPE)
        for r in range(N):
            for c in range(N):
                C[r, c] = right_log[r + c + N - 1, r]
        return C

    def run_compute_and_drain(self, B: np.ndarray) -> np.ndarray:
        right_log = self._run_internal(B)
        return self._unskew(right_log, self.size)

    def run_tile(self, A: np.ndarray, B: np.ndarray) -> np.ndarray:
        self.reset()
        self.load_weights(A)
        return self.run_compute_and_drain(B)

    def run_tile_traced(self, A: np.ndarray, B: np.ndarray):
        """Like run_tile, but also returns the per-cycle right-edge log so a
        testbench can check c_out every cycle, not just at final positions.

        Returns:
            (C, right_log) where right_log has shape (3N-2, N).
        """
        self.reset()
        self.load_weights(A)
        right_log = self._run_internal(B)
        C = self._unskew(right_log, self.size)
        return C, right_log