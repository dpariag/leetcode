// Leetcode: https://leetcode.com/problems/set-matrix-zeroes/
// Given an MxN matrix, if an element is 0, set its entire row and column to be zero. Do it in place.

// Approach: Use the first row and column to record the rows/cols that need to be zeroed.
// Requires special handling of matrix[0][0] and all of the first row/col
// Acceptance: 40.8%

#include <vector>
#include <iostream>
#include <assert.h>
#include "debug.h"

using Matrix = std::vector<std::vector<int>>;

// Accepted. 44ms. Faster than 92.46% of C++ submissions
class Solution {
public:
  void setZeroes(Matrix& matrix) {
    if (matrix.empty() || matrix[0].empty()) { return; }
    bool clear_first_row = false, clear_first_col = false;

    // Check the first column
    for (int row = 0; row < matrix.size(); ++row) {
      if (matrix[row][0] == 0) { clear_first_col = true; break; }
    } // for

    // Check the first row
    for (int col = 0; col < matrix[0].size(); ++col) {
      if (matrix[0][col] == 0) { clear_first_row = true; break; }
    } //for

    // Scan other rows and cols
    for (int row = 1; row < matrix.size(); ++row) {
      for (int col = 1; col < matrix[row].size(); ++col) {
        if (matrix[row][col] == 0) {
          matrix[row][0] = 0;
          matrix[0][col] = 0;
        } // if
      } // for col
    } // for row

    for (int row = 1; row < matrix.size(); ++row) {
      if (matrix[row][0] == 0) {
        for (int col = 1; col < matrix[row].size(); ++ col) {
          matrix[row][col] = 0;
        } // for col
      } // if
    } // for row

    for (int col = 1; col < matrix[0].size(); ++col) {
      if (matrix[0][col] == 0) {
        for (int row = 1; row < matrix.size(); ++row) {
          matrix[row][col] = 0;
        } // for row
      } // if
    } // for col

    if (clear_first_row) {
      for (int col = 0; col < matrix[0].size(); ++col) { matrix[0][col] = 0; }
    }

    if (clear_first_col) {
      for (int row = 0; row < matrix.size(); ++row) { matrix[row][0] = 0; }
    }
  }
};

bool test_matrix_zeroes(Matrix m, const Matrix& expected) {
  Solution soln;
  soln.setZeroes(m);
  return m == expected;
}

void test_matrix_zeroes() {
  assert(test_matrix_zeroes({{1,0,1},{1,1,1},{2,2,2}}, {{0,0,0},{1,0,1},{2,0,2}}));
  assert(test_matrix_zeroes({{1,0,1,0},{1,1,1,0},{2,2,2,0}}, {{0,0,0,0},{0,0,0,0},{0,0,0,0}}));
  assert(test_matrix_zeroes({{1,1,1,1},{1,1,1,1},{2,2,2,2}}, {{1,1,1,1},{1,1,1,1},{2,2,2,2}}));
  assert(test_matrix_zeroes({{1,1,1,1},{1,1,1,1},{2,0,2,0}}, {{1,0,1,0},{1,0,1,0},{0,0,0,0}}));
}

int main(int argc, char** argv) {
  test_matrix_zeroes();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
