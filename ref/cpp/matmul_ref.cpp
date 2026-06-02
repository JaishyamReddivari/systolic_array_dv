// matmul_ref.cpp
//
// Implementation of the INT8 matmul reference. See matmul_ref.h for the
// contract. Mirrors ref/python/golden.py numerically.

#include "matmul_ref.h"

void matmul_int8(const int8_t* A, const int8_t* B, int32_t* C, int N) {
    // Three nested loops -- the textbook GEMM structure.
    //   r : output row    (row of A, row of C)
    //   c : output column (column of B, column of C)
    //   k : inner index   (column of A, row of B) -- the dimension summed over
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {

            // Accumulator MUST be int32. This mirrors the hardware's INT32
            // accumulator (spec section 6.1) and golden.py's int32 dtype.
            // If this were int8 or int16 it would overflow: worst case is
            // 8 * (-128 * -128) = 131072, which exceeds int16's 32767 limit.
            int32_t acc = 0;

            for (int k = 0; k < N; ++k) {
                // A[r][k] in row-major flattening is A[r*N + k]. Same for B.
                int8_t a = A[r * N + k];
                int8_t b = B[k * N + c];

                // The multiply. SUBTLE BUT IMPORTANT:
                // In C++, int8_t * int8_t does NOT produce an int8_t. Both
                // operands are first promoted to `int` (the "usual arithmetic
                // conversions"), so the multiply happens in (at least) 32-bit
                // int space. That is exactly what we want -- it prevents the
                // product from overflowing, matching how golden.py casts to
                // int32 before multiplying.
                //
                // We write the cast to int32_t explicitly so the intent is
                // visible and the behavior is identical on every compiler,
                // rather than relying on implicit promotion being "wide enough".
                int32_t product = static_cast<int32_t>(a) * static_cast<int32_t>(b);

                // Accumulate in int32. Plain two's-complement addition --
                // no saturation, no clamping. Matches NumPy int32 semantics.
                acc += product;
            }

            // Store the finished dot product. C[r][c] -> C[r*N + c].
            C[r * N + c] = acc;
        }
    }
}