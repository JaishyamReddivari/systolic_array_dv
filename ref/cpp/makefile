# Makefile for the C++ INT8 matmul reference.
#
#   make            -> build the standalone test binary
#   make test       -> build and run the self-test
#   make crosscheck -> build, then cross-check against the NumPy models
#   make clean      -> remove build artifacts

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
BIN      := test_matmul
SRC      := matmul_ref.cpp test_matmul_ref.cpp

$(BIN): $(SRC) matmul_ref.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

.PHONY: test
test: $(BIN)
	./$(BIN)

.PHONY: crosscheck
crosscheck: $(BIN)
	python3 crosscheck.py

.PHONY: clean
clean:
	rm -f $(BIN) _vec.txt