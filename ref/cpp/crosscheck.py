#!/usr/bin/env python3
"""Cross-check the C++ reference against the NumPy models.

Generates random INT8 matrix pairs, feeds the SAME inputs to:
  - the C++ reference (via its --vectors mode)
  - the NumPy behavioral golden (golden.py)
  - the NumPy cycle-accurate simulator (systolic_sim.py)
and confirms all three produce identical INT32 results.

Run from the repo root (so the ref/python modules import cleanly):
    g++ -std=c++17 -O2 cpp/matmul_ref.cpp cpp/test_matmul_ref.cpp -o cpp/test_matmul
    python cpp/crosscheck.py
"""

import os
import sys
import subprocess
import numpy as np

# Allow importing the Python models regardless of where we're invoked from.
HERE = os.path.dirname(os.path.abspath(__file__))
REF_DIR = os.path.dirname(HERE)
sys.path.insert(0, os.path.join(REF_DIR, "python"))

from golden import matmul_int8                 # noqa: E402
from systolic_sim import SystolicArray         # noqa: E402

CPP_BINARY = os.path.join(HERE, "test_matmul")
VEC_FILE = os.path.join(HERE, "_vec.txt")
N = 8
NUM_TRIALS = 200


def cpp_matmul(A: np.ndarray, B: np.ndarray) -> np.ndarray:
    """Run the C++ reference on A, B via its vector-file interface."""
    with open(VEC_FILE, "w") as f:
        f.write(" ".join(str(int(x)) for x in A.flatten()) + "\n")
        f.write(" ".join(str(int(x)) for x in B.flatten()) + "\n")

    result = subprocess.run([CPP_BINARY, "--vectors", VEC_FILE],
                            capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError(f"C++ binary failed: {result.stderr}")

    return np.array([[int(v) for v in line.split()]
                     for line in result.stdout.strip().split("\n")],
                    dtype=np.int32)


def main() -> int:
    if not os.path.exists(CPP_BINARY):
        print(f"ERROR: {CPP_BINARY} not found. Build it first:")
        print("  g++ -std=c++17 -O2 cpp/matmul_ref.cpp cpp/test_matmul_ref.cpp -o cpp/test_matmul")
        return 1

    rng = np.random.default_rng(12345)
    arr = SystolicArray()
    mismatches = 0

    for trial in range(NUM_TRIALS):
        A = rng.integers(-128, 128, (N, N), dtype=np.int8)
        B = rng.integers(-128, 128, (N, N), dtype=np.int8)

        c_cpp = cpp_matmul(A, B)
        c_golden = matmul_int8(A, B)
        c_sim = arr.run_tile(A, B)

        if not (np.array_equal(c_cpp, c_golden) and
                np.array_equal(c_sim, c_golden)):
            mismatches += 1
            print(f"MISMATCH on trial {trial}")
            print(f"  C++  == golden: {np.array_equal(c_cpp, c_golden)}")
            print(f"  sim  == golden: {np.array_equal(c_sim, c_golden)}")

    if os.path.exists(VEC_FILE):
        os.remove(VEC_FILE)

    if mismatches == 0:
        print(f"PASS: {NUM_TRIALS} trials, three-way agreement "
              f"(C++ ref / NumPy golden / cycle-accurate sim).")
        return 0
    else:
        print(f"FAIL: {mismatches}/{NUM_TRIALS} trials mismatched.")
        return 1


if __name__ == "__main__":
    sys.exit(main())