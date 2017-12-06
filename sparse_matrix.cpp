// Leetcode: https://leetcode.com/problems/sparse-matrix-multiplication/description/
// Given two sparse matrices A and B, return the result of A*B.
// You may assume that A's column number is equal to B's row number.

// Brute Force: Perform regular matrix multiplication. O(N^3) time.
// Better: Pre-process the matrix to find the locations of all-zero rows and cols.

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 16ms. Beats 43.29% of submissions, ties 27.36% of submissions.
class Solution {
public:
    Matrix multiply(Matrix& A, Matrix& B) {
        if (A.empty() || B.empty()) { return Matrix(); }

        std::vector<bool> zero_rows(A[0].size(), false), zero_cols(B.size(), false);

        // Find non-zero rows
        for (int row = 0; row < A.size(); ++row) {
            auto row_is_zero = true;
            for (int col = 0; col < A[0].size(); ++col) {
                if (A[row][col] != 0) { row_is_zero = false; break; }
            }
            zero_rows[row] = row_is_zero;
        }

        // Find non-zero cols
        for (int col = 0; col < B[0].size(); ++col) {
            auto col_is_zero = true;
            for (int row = 0; row < B.size(); ++row) {
                if (B[row][col] != 0) { col_is_zero = false; break; }
            }
            zero_cols[col] = col_is_zero;
        }
        
        Matrix result(A.size(), std::vector<int>(B[0].size(), 0));
        for (int a_row = 0; a_row < A.size(); ++a_row) {
            if (zero_rows[a_row]) { continue; }
            for (int b_col = 0; b_col < B[0].size(); ++b_col) {
                if (zero_cols[b_col]) { continue; }
                int value = 0;
                for (int i = 0; i < A[0].size(); ++i) {
                    value += (A[a_row][i] * B[i][b_col]);
                }
                result[a_row][b_col] = value;
            }
        }
        return result;
    }
};

bool test_matrix_multiply(Matrix a, Matrix b, Matrix expected) {
    Solution soln;
    return soln.multiply(a,b) == expected;
}

void test_matrix_multiply() {
    assert(test_matrix_multiply({{2,2,2},{2,2,2}}, {{4,4},{4,4},{4,4}}, {{24,24},{24,24}}));
    assert(test_matrix_multiply({{2,2,2},{2,2,2}}, {{4,0},{4,0},{4,0}}, {{24,0},{24,0}}));
    assert(test_matrix_multiply({{2,2,2},{2,2,2}}, {{0,4},{0,4},{0,4}}, {{0,24},{0,24}}));
    assert(test_matrix_multiply({{0,0,0},{2,2,2}}, {{4,4},{4,4},{4,4}}, {{0,0},{24,24}}));
    assert(test_matrix_multiply({{2,2,2},{0,0,0}}, {{4,4},{4,4},{4,4}}, {{24,24},{0,0}}));
}

int main(int argc, char** argv) {
    test_matrix_multiply();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
