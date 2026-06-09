// test_matmul_ref.cpp
//
// Standalone test harness for the C++ reference model.
//   - Self-test (default, no args): runs built-in cases and checks them.
//   - Vector mode (--vectors <file>): reads A,B from a file, writes C to stdout,
//     so the Python cross-check can feed identical inputs to the NumPy models.
//
// Build:   g++ -std=c++17 -O2 matmul_ref.cpp test_matmul_ref.cpp -o test_matmul
// Run:     ./test_matmul                    (self-test)
//          ./test_matmul --vectors in.txt   (vector mode)

#include "matmul_ref.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

static const int N = 8;

static void print_matrix(const int32_t* M) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            std::cout << M[r * N + c];
            if (c < N - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

static bool run_self_tests() {
    bool all_ok = true;

    // Test 1: hand-computed 2x2 (same as the Python tests), padded into 8x8.
    //   [[1,2],[3,4]] * [[5,6],[7,8]] = [[19,22],[43,50]]
    {
        int8_t A[N * N] = {0};
        int8_t B[N * N] = {0};
        int32_t C[N * N] = {0};

        A[0 * N + 0] = 1; A[0 * N + 1] = 2;
        A[1 * N + 0] = 3; A[1 * N + 1] = 4;
        B[0 * N + 0] = 5; B[0 * N + 1] = 6;
        B[1 * N + 0] = 7; B[1 * N + 1] = 8;

        matmul_int8(A, B, C, N);

        bool ok = (C[0 * N + 0] == 19) && (C[0 * N + 1] == 22) &&
                  (C[1 * N + 0] == 43) && (C[1 * N + 1] == 50);
        std::cout << "Test 1 (hand 2x2):        " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) {
            std::cout << "  got [" << C[0] << "," << C[1] << ","
                      << C[N] << "," << C[N + 1] << "] expected [19,22,43,50]\n";
        }
        all_ok &= ok;
    }

    // Test 2: all -128. Each output = 8 * (-128 * -128) = 131072 -- the case
    // that catches a silent overflow into a narrower-than-int32 type.
    {
        int8_t A[N * N];
        int8_t B[N * N];
        int32_t C[N * N];
        std::memset(C, 0, sizeof(C));
        for (int i = 0; i < N * N; ++i) { A[i] = -128; B[i] = -128; }

        matmul_int8(A, B, C, N);

        bool ok = true;
        for (int i = 0; i < N * N; ++i) {
            if (C[i] != 131072) { ok = false; break; }
        }
        std::cout << "Test 2 (extreme -128):    " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) std::cout << "  got C[0]=" << C[0] << " expected 131072\n";
        all_ok &= ok;
    }

    // Test 3: identity * M = M -- sanity check on indexing/orientation.
    {
        int8_t A[N * N] = {0};
        int8_t B[N * N];
        int32_t C[N * N];
        std::memset(C, 0, sizeof(C));
        for (int i = 0; i < N; ++i) A[i * N + i] = 1;
        for (int i = 0; i < N * N; ++i) B[i] = (int8_t)(i - 30);

        matmul_int8(A, B, C, N);

        bool ok = true;
        for (int i = 0; i < N * N; ++i) {
            if (C[i] != static_cast<int32_t>(B[i])) { ok = false; break; }
        }
        std::cout << "Test 3 (identity):        " << (ok ? "PASS" : "FAIL") << '\n';
        all_ok &= ok;
    }

    return all_ok;
}

// Vector mode file format: 64 ints for A (row-major), then 64 for B; output is
// 64 ints for C, 8 per line. Lets the Python cross-check compare on identical inputs.
static int run_vector_mode(const char* path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "ERROR: cannot open " << path << '\n';
        return 1;
    }

    int8_t A[N * N];
    int8_t B[N * N];
    int32_t C[N * N];
    std::memset(C, 0, sizeof(C));

    // Read via int, then narrow: reading directly into int8_t parses as a
    // character on many stream implementations.
    for (int i = 0; i < N * N; ++i) {
        int v;
        if (!(in >> v)) { std::cerr << "ERROR: not enough values for A\n"; return 1; }
        A[i] = static_cast<int8_t>(v);
    }
    for (int i = 0; i < N * N; ++i) {
        int v;
        if (!(in >> v)) { std::cerr << "ERROR: not enough values for B\n"; return 1; }
        B[i] = static_cast<int8_t>(v);
    }

    matmul_int8(A, B, C, N);
    print_matrix(C);
    return 0;
}

int main(int argc, char** argv) {
    if (argc >= 3 && std::strcmp(argv[1], "--vectors") == 0) {
        return run_vector_mode(argv[2]);
    }

    bool ok = run_self_tests();
    std::cout << '\n' << (ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << '\n';
    return ok ? 0 : 1;
}
