"""Tests for the behavioral golden model."""

import numpy as np
import pytest

from golden import matmul_int8


def test_hand_example():
    """A 2x2 example we can verify with pencil and paper.

        A = [[1, 2],     B = [[5, 6],     C = [[19, 22],
             [3, 4]]          [7, 8]]          [43, 50]]
    """
    A = np.array([[1, 2], [3, 4]], dtype=np.int8)
    B = np.array([[5, 6], [7, 8]], dtype=np.int8)
    expected = np.array([[19, 22], [43, 50]], dtype=np.int32)

    C = matmul_int8(A, B)

    assert C.dtype == np.int32, "Output must be int32"
    assert np.array_equal(C, expected), f"Got {C}, expected {expected}"


def test_8x8_random():
    """The actual DUT tile size. Compare against NumPy's own matmul
    with int32 inputs (which we trust)."""
    rng = np.random.default_rng(seed=42)
    A = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)
    B = rng.integers(-128, 128, size=(8, 8), dtype=np.int8)

    C = matmul_int8(A, B)
    expected = A.astype(np.int32) @ B.astype(np.int32)

    assert np.array_equal(C, expected)


def test_extreme_values_no_overflow():
    """Stress test: maximum-magnitude INT8 values. Per spec §6.2,
    overflow is mathematically impossible for K=8. Verify."""
    A = np.full((8, 8), -128, dtype=np.int8)   # most-negative INT8
    B = np.full((8, 8), -128, dtype=np.int8)

    C = matmul_int8(A, B)
    # Each element: 8 * (-128) * (-128) = 131072. Well within INT32.
    assert (C == 131072).all()
    assert C.dtype == np.int32


def test_rejects_wrong_dtype():
    """Hardware-style type checking: int32 input is a contract violation."""
    A = np.ones((8, 8), dtype=np.int32)
    B = np.ones((8, 8), dtype=np.int8)
    with pytest.raises(AssertionError):
        matmul_int8(A, B)