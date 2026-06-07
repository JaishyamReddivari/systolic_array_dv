#!/usr/bin/env python3
"""Generate expected vectors for tb_controller.sv.

Uses the proven behavioral golden (golden.matmul_int8) as the reference for
C = A * B. The controller testbench drives A and B as AXI-Stream beats and
checks the C beats against these expected values. Because the reference is
already proven (vs C++ and the hand example), a mismatch isolates to the RTL.

File format (whitespace-separated decimal ints; row-major):
  line 1:           N_TILES
  per tile:
     8 lines x 8 ints  -> rows of A   (A[r][0..7])
     8 lines x 8 ints  -> rows of B   (B[k][0..7])
     8 lines x 8 ints  -> rows of C   (expected, C[r][0..7])
"""

import os, sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(REPO_ROOT, "ref", "python"))
sys.path.insert(0, HERE)
sys.path.insert(0, REPO_ROOT)

from golden import matmul_int8  # noqa: E402

N = 8
OUT = os.path.join(HERE, "controller_vectors.txt")


def main() -> int:
    tiles = []

    # 1) hand example padded
    A = np.zeros((N, N), np.int8); B = np.zeros((N, N), np.int8)
    A[:2, :2] = [[1, 2], [3, 4]]; B[:2, :2] = [[5, 6], [7, 8]]
    tiles.append((A, B))

    # 2) identity * arbitrary -> C == B
    A = np.eye(N, dtype=np.int8)
    B = (np.arange(N * N, dtype=np.int64).reshape(N, N) - 30).astype(np.int8)
    tiles.append((A, B))

    # 3) extreme -128
    A = np.full((N, N), -128, np.int8); B = np.full((N, N), -128, np.int8)
    tiles.append((A, B))

    # 4,5,6) random seeded
    rng = np.random.default_rng(2025)
    for _ in range(3):
        A = rng.integers(-128, 128, (N, N), dtype=np.int8)
        B = rng.integers(-128, 128, (N, N), dtype=np.int8)
        tiles.append((A, B))

    lines = [str(len(tiles))]
    for (A, B) in tiles:
        C = matmul_int8(A, B)
        for r in range(N):
            lines.append(" ".join(str(int(x)) for x in A[r]))
        for k in range(N):
            lines.append(" ".join(str(int(x)) for x in B[k]))
        for r in range(N):
            lines.append(" ".join(str(int(x)) for x in C[r]))

    with open(OUT, "w") as f:
        f.write("\n".join(lines) + "\n")
    print(f"Wrote {OUT}  ({len(tiles)} tiles)")
    return 0


if __name__ == "__main__":
    sys.exit(main())