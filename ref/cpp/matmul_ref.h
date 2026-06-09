// matmul_ref.h
//
// INT8 matrix-multiply reference model for systolic_array_dv.
// C++ counterpart to ref/python/golden.py: same function, INT8 operands with
// INT32 accumulation, matching NumPy bit-for-bit.
//
// Mirrors the behavioral golden (the correct answer), not the cycle-accurate
// model -- the scoreboard only needs the result; timing is checked via SVA and
// the Python cycle-accurate model.
//
// The core compute is a plain C-style free function (pointers + dimensions) so
// it can later be exported to SystemVerilog via DPI-C with no rewrite.
#ifndef MATMUL_REF_H
#define MATMUL_REF_H
#include <cstdint>
// Compute C = A * B for square N x N INT8 matrices.
//
// Args:
//   A : N*N int8 values, row-major. A[r*N + k] is A[r][k].
//   B : N*N int8 values, row-major. B[k*N + c] is B[k][c].
//   C : N*N int32 values, row-major (output). C[r*N + c] = C[r][c].
//   N : matrix dimension (8 for the DUT tile).
//
// Numerical contract (must match golden.py): int8 * int8 promoted to int32,
// int32 accumulation, no saturation or rounding.
void matmul_int8(const int8_t* A, const int8_t* B, int32_t* C, int N);
#endif  // MATMUL_REF_H
