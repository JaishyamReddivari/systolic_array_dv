// matmul_ref.h
//
// INT8 matrix-multiply reference model for systolic_array_dv.
//
// This is the C++ counterpart to ref/python/golden.py. It computes the SAME
// function: C = A * B, with INT8 operands and INT32 accumulation, matching
// NumPy's arithmetic bit-for-bit.
//
// It mirrors the BEHAVIORAL golden (the "what is the right answer" model),
// not the cycle-accurate simulator. The DV scoreboard only needs to know the
// correct result; cycle-level timing is checked separately via SVA and the
// Python cycle-accurate model.
//
// Structure note: the core compute is a free function with a plain C-style
// signature (pointers + dimensions). This is deliberate so it can later be
// exported to SystemVerilog via DPI-C with no rewrite -- DPI imports map
// cleanly onto exactly this kind of signature.

#ifndef MATMUL_REF_H
#define MATMUL_REF_H

#include <cstdint>

// Compute C = A * B for square N x N INT8 matrices.
//
// Args:
//   A : pointer to N*N int8 values, row-major. A[r*N + k] is A[r][k].
//   B : pointer to N*N int8 values, row-major. B[k*N + c] is B[k][c].
//   C : pointer to N*N int32 values, row-major (output). C[r*N + c] = C[r][c].
//   N : matrix dimension (8 for the DUT tile).
//
// Numerical contract (must match golden.py):
//   - Each product is a signed int8 * int8, promoted to int32.
//   - Accumulation is in int32.
//   - No saturation, no rounding -- plain two's-complement int32 add.
void matmul_int8(const int8_t* A, const int8_t* B, int32_t* C, int N);

#endif  // MATMUL_REF_H