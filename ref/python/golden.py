"""Behavioral golden model for 8x8 INT8 systolic array."""

import numpy as np


def matmul_int8(A: np.ndarray, B: np.ndarray) -> np.ndarray:
    """Compute C = A @ B with INT8 inputs and INT32 accumulation."""
    assert A.dtype == np.int8, f"A must be int8, got {A.dtype}"
    assert B.dtype == np.int8, f"B must be int8, got {B.dtype}"
    assert A.shape[1] == B.shape[0], f"Inner dims must match: {A.shape} vs {B.shape}"

    A32 = A.astype(np.int32)
    B32 = B.astype(np.int32)
    return A32 @ B32