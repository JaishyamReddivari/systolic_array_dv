"""Tests for the cycle-accurate systolic simulator."""

import numpy as np
import pytest

from golden import matmul_int8
from systolic_sim import SystolicArray


def test_hand_example():
    """A 2x2 example we can verify with pencil and paper, padded to 8x8."""
    A = np.zeros((8, 8), dtype=np.int8)
    B = np.zeros((8, 8), dtype=np.int8)
    A[:2, :2] = [[1, 2], [3, 4]]
    B[:2, :2] = [[5, 6], [7, 8]]

    arr = SystolicArray()
    C = arr.run_tile(A, B)

    expected = matmul_int8(A, B)
    assert np.array_equal(C, expected), f"\nGot:\n{C}\nExpected:\n{expected}"


def test_random_matches_golden():
    """100 random matmuls. Sim and golden must agree on every one."""
    rng = np.random.default_rng(seed=0)
    arr = SystolicArray()

    for trial in range(100):
        A = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)
        B = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)

        C_sim = arr.run_tile(A, B)
        C_golden = matmul_int8(A, B)

        assert np.array_equal(C_sim, C_golden), (
            f"Mismatch on trial {trial}:\n"
            f"A=\n{A}\nB=\n{B}\n"
            f"Sim:\n{C_sim}\nGolden:\n{C_golden}"
        )


def test_extreme_values():
    """Worst-case stimulus: all -128. Should produce 131072 in every cell."""
    A = np.full((8, 8), -128, dtype=np.int8)
    B = np.full((8, 8), -128, dtype=np.int8)

    arr = SystolicArray()
    C = arr.run_tile(A, B)

    assert (C == 131072).all(), f"Expected all 131072, got:\n{C}"


def test_back_to_back_tiles():
    """Two tiles in succession. Second tile must not be corrupted by first."""
    rng = np.random.default_rng(seed=1)
    arr = SystolicArray()

    A1 = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)
    B1 = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)
    A2 = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)
    B2 = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)

    C1 = arr.run_tile(A1, B1)
    C2 = arr.run_tile(A2, B2)

    assert np.array_equal(C1, matmul_int8(A1, B1))
    assert np.array_equal(C2, matmul_int8(A2, B2)), \
        "Tile 2 was contaminated by tile 1 state — reset bug."