// Leetcode: https://leetcode.com/problems/spiral-matrix/description/
// Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 0ms. Beats 60.88% of submissions, ties 39.12% of submissions.
class Solution {
public:
    std::vector<int> spiralOrder(const Matrix& matrix) {
        std::vector<int> result;        
        if (matrix.empty()) { return result; }

        result.reserve(matrix.size() * matrix[0].size());
        int top_row = 0, bottom_row = matrix.size() - 1;
        int left_col = 0, right_col = matrix[0].size() - 1;

        while (top_row <= bottom_row && left_col <= right_col) {
            // Add top row going left to right
            for (int col = left_col; col <= right_col; ++col) { result.emplace_back(matrix[top_row][col]); }
            if (top_row == bottom_row) { break; }   
            
            // Add right column, going top to bottom
            for (int row = top_row+1; row < bottom_row; ++row) { result.emplace_back(matrix[row][right_col]); }
            
            // Add bottom row, going right to left
            for (int col = right_col; col >= left_col; --col) { result.emplace_back(matrix[bottom_row][col]); }
            if (left_col == right_col) { break; }
            
            // Add the left column, going bottom to top
            for (int row = bottom_row-1; row > top_row; --row) { result.emplace_back(matrix[row][left_col]); }
            ++top_row, --bottom_row, --right_col, ++left_col;
        }
        return result;
    }
};

bool test_spiral_matrix(Matrix m, std::vector<int> expected) {
    Solution soln;
    return soln.spiralOrder(m) == expected;
}

void test_spiral_matrix() {
    assert(test_spiral_matrix({{}}, {}));
    assert(test_spiral_matrix({{1}}, {1}));
    assert(test_spiral_matrix({{1,2,3,4}}, {1,2,3,4}));         // one row
    assert(test_spiral_matrix({{1},{2},{3},{4}}, {1,2,3,4}));   // one col
    assert(test_spiral_matrix({{1,2},{3,4}}, {1,2,4,3}));       // two rows
    assert(test_spiral_matrix({{1,2},{3,4},{5,6}}, {1,2,4,6,5,3}));
    assert(test_spiral_matrix({{1,2,3},{4,5,6},{7,8,9}}, {1,2,3,6,9,8,7,4,5}));
}

int main(int argc, char** argv) {
    test_spiral_matrix();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
