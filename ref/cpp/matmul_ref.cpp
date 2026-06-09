// matmul_ref.cpp
//
// INT8 matmul reference. See matmul_ref.h for the contract.
// Numerically mirrors ref/python/golden.py.
#include "matmul_ref.h"
void matmul_int8(const int8_t* A, const int8_t* B, int32_t* C, int N) {
    // r = output row, c = output column, k = summed inner index (col of A / row of B).
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            // Accumulator must be int32 to match the hardware's INT32 accumulator
            // (spec 6.1) and golden.py. int16 would overflow: worst case
            // 8 * (-128 * -128) = 131072 > int16's 32767.
            int32_t acc = 0;
            for (int k = 0; k < N; ++k) {
                int8_t a = A[r * N + k];
                int8_t b = B[k * N + c];
                // Cast to int32 before multiplying. int8 * int8 already promotes
                // both operands to int (usual arithmetic conversions), so the
                // product can't overflow -- the explicit widening just makes the
                // intent clear and the behavior identical across compilers,
                // matching golden.py casting to int32 first.
                int32_t product = static_cast<int32_t>(a) * static_cast<int32_t>(b);
                // Plain two's-complement add: no saturation, matching NumPy int32.
                acc += product;
            }
            C[r * N + c] = acc;
        }
    }
}
