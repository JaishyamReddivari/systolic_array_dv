// test_matmul_ref.cpp
//
// Standalone test harness for the C++ reference model.
//
// Two modes:
//   1. Self-test (default, no args): runs built-in cases and checks them.
//   2. Vector mode (--vectors <file>): reads input matrices from a file,
//      writes computed outputs to stdout. Used to cross-check against the
//      NumPy models on IDENTICAL inputs (next task).
//
// Build:   g++ -std=c++17 -O2 matmul_ref.cpp test_matmul_ref.cpp -o test_matmul
// Run:     ./test_matmul              (self-test)
//          ./test_matmul --vectors in.txt   (vector mode)

#include "matmul_ref.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

static const int N = 8;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

// Print an N x N int32 matrix, one row per line, space-separated.
static void print_matrix(const int32_t* M) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            std::cout << M[r * N + c];
            if (c < N - 1) std::cout << ' ';
        }
        std::cout << '\n';
    }
}

// ---------------------------------------------------------------------------
// Self-test cases
// ---------------------------------------------------------------------------

// Returns true if all self-tests pass.
static bool run_self_tests() {
    bool all_ok = true;

    // --- Test 1: hand-computed 2x2 example, padded into the top-left of 8x8 ---
    // Same example as the Python tests:
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

    // --- Test 2: extreme values, all -128 ---
    // Each output = 8 * (-128 * -128) = 8 * 16384 = 131072.
    // This is the key test that the int32 path is correct and nothing
    // silently overflowed to a narrower type.
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

    // --- Test 3: identity * M = M ---
    // Sanity check on indexing/orientation. If A is identity, C must equal B.
    {
        int8_t A[N * N] = {0};
        int8_t B[N * N];
        int32_t C[N * N];
        std::memset(C, 0, sizeof(C));
        for (int i = 0; i < N; ++i) A[i * N + i] = 1;       // identity
        for (int i = 0; i < N * N; ++i) B[i] = (int8_t)(i - 30);  // arbitrary

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

// ---------------------------------------------------------------------------
// Vector mode: read A and B from a file, compute C, print C.
// ---------------------------------------------------------------------------
//
// File format (plain text):
//   - 64 integers for A (row-major), whitespace-separated
//   - 64 integers for B (row-major), whitespace-separated
// Output: 64 integers for C (row-major), 8 per line.
//
// This lets the Python cross-check script generate random A,B, feed the SAME
// numbers to this program, and compare C against the NumPy result.

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

    // Read into a temporary int (file holds decimal ints like -128..127),
    // then narrow to int8_t. Reading directly into int8_t would parse as a
    // character on many stream implementations, so we go via int.
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

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char** argv) {
    if (argc >= 3 && std::strcmp(argv[1], "--vectors") == 0) {
        return run_vector_mode(argv[2]);
    }

    // Default: self-test.
    bool ok = run_self_tests();
    std::cout << '\n' << (ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED") << '\n';
    return ok ? 0 : 1;
}