#!/usr/bin/env python3
"""Generate golden stimulus vectors for tb_systolic_array.sv.

This script is NOT a testbench. It runs the proven cycle-accurate model
(systolic_sim.py) offline and writes a plain-text vector file that the
SystemVerilog testbench replays against the RTL. The SV testbench contains
NO skew or timing logic of its own -- it just drives these exact pin values
and checks these exact expected outputs. That keeps the test independent of
the controller logic it will later verify.

For each test tile we emit:
  - the weight_top feed for each of the 8 LOAD cycles (last-row-first, so the
    shift chain leaves PE(r,k) holding A[r][k])
  - the a_top feed for each of the 3N-2 = 22 COMPUTE/DRAIN cycles (skewed)
  - the expected c_out for each compute cycle (= right_log[cycle])

File format (all whitespace-separated integers, parser-friendly for $fscanf):
  line 1:        N  N_LOAD  N_COMPUTE  N_TILES
  per tile:
     N_LOAD lines   of 8 ints   -> weight_top[0..7] for that load cycle
     N_COMPUTE lines of 16 ints  -> a_top[0..7] then expected c_out[0..7]
"""

import os
import sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(REPO_ROOT, "ref", "python"))
# Fallback: also try local (when sim sits next to this script during dev)
sys.path.insert(0, HERE)

from systolic_sim import SystolicArray  # noqa: E402

N = 8
N_LOAD = N            # 8 cycles to shift weights in
N_COMPUTE = 3 * N - 2  # 22 cycles for compute + drain
OUT_PATH = os.path.join(HERE, "stimulus.txt")


def weight_feed_for_tile(A: np.ndarray) -> np.ndarray:
    """weight_top[c][j] for each load cycle c.

    The PE weight chain shifts DOWN: feeding value v on cycle c into the top
    of column j lands in PE(7,j) after 8 shifts if v was fed first. To leave
    PE(r,j) = A[r][j], feed last-row-first: cycle 0 -> row 7, ... cycle 7 ->
    row 0. So weight_top[c][j] = A[N-1-c][j].
    """
    feed = np.zeros((N_LOAD, N), dtype=np.int64)
    for c in range(N_LOAD):
        for j in range(N):
            feed[c, j] = int(A[N - 1 - c, j])
    return feed


def activation_feed_for_tile(B: np.ndarray) -> np.ndarray:
    """a_top[c][j] for each compute cycle c: the skewed B, zero-padded past
    the staircase (cycles >= 2N-1 feed zeros, i.e. the DRAIN tail)."""
    skewed = SystolicArray._skew_b_input(B)  # (2N-1, N)
    feed = np.zeros((N_COMPUTE, N), dtype=np.int64)
    for c in range(N_COMPUTE):
        if c < skewed.shape[0]:
            feed[c, :] = skewed[c, :].astype(np.int64)
        # else leave zeros (drain)
    return feed


def main() -> int:
    # Directed test tiles. Mix of hand-verifiable and random-but-seeded.
    tiles = []

    # 1) hand example, padded
    A = np.zeros((N, N), dtype=np.int8); B = np.zeros((N, N), dtype=np.int8)
    A[:2, :2] = [[1, 2], [3, 4]]; B[:2, :2] = [[5, 6], [7, 8]]
    tiles.append((A, B))

    # 2) identity * arbitrary  (C should equal B)
    A = np.eye(N, dtype=np.int8)
    B = (np.arange(N * N, dtype=np.int64).reshape(N, N) - 30).astype(np.int8)
    tiles.append((A, B))

    # 3) extreme values
    A = np.full((N, N), -128, dtype=np.int8); B = np.full((N, N), -128, dtype=np.int8)
    tiles.append((A, B))

    # 4,5) random, seeded for reproducibility
    rng = np.random.default_rng(2025)
    for _ in range(2):
        A = rng.integers(-128, 128, (N, N), dtype=np.int8)
        B = rng.integers(-128, 128, (N, N), dtype=np.int8)
        tiles.append((A, B))

    arr = SystolicArray()
    lines = [f"{N} {N_LOAD} {N_COMPUTE} {len(tiles)}"]

    for (A, B) in tiles:
        wfeed = weight_feed_for_tile(A)
        afeed = activation_feed_for_tile(B)
        _, right_log = arr.run_tile_traced(A, B)  # right_log[c][r] expected c_out

        for c in range(N_LOAD):
            lines.append(" ".join(str(int(x)) for x in wfeed[c]))
        for c in range(N_COMPUTE):
            row = list(afeed[c]) + list(int(x) for x in right_log[c])
            lines.append(" ".join(str(int(x)) for x in row))

    with open(OUT_PATH, "w") as f:
        f.write("\n".join(lines) + "\n")

    print(f"Wrote {OUT_PATH}")
    print(f"  {len(tiles)} tiles, {N_LOAD} load + {N_COMPUTE} compute cycles each")
    return 0


if __name__ == "__main__":
    sys.exit(main())