// Leetcode: https://leetcode.com/problems/diagonal-traverse/description/
// Given a matrix, return its element in the diagonal ordering shown in the URL above.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;
using Traversal = std::vector<int>;

// Accepted. 72ms. Beats 98.40% of submissions, ties 1.60% of submissions.
class Solution {
public:
    Traversal findDiagonalOrder(Matrix& matrix) {
        Traversal traversal;
        if (matrix.empty()) { return traversal; }
        
        traversal.reserve(matrix.size() * matrix[0].size());
        int num_rows = matrix.size(), num_cols = matrix[0].size();
        int row = 0, col = 0;
        int inc = -1;

        while (row < num_rows && col < num_cols) {

            traversal.emplace_back(matrix[row][col]);
           
            int old_row = row, old_col = col; 
            row += inc, col -=inc;
            
            if (row < 0 || row >= num_rows) { row = old_row, col = old_col+1; }
            if (col < 0 || col >= num_cols) { col = old_col, row = old_row+1; }
            if (row == old_row || col == old_col) { inc = -inc; }
        }
        return traversal;
    }
};

bool test_diagonal_order(Matrix m, Traversal expected) {
    Solution soln;
    auto traversal = soln.findDiagonalOrder(m);
    return traversal == expected;
}

void test_diagonal_order() {
    assert(test_diagonal_order({}, {}));
    assert(test_diagonal_order({{1}}, {1}));
    assert(test_diagonal_order({{1},{2},{3}}, {1,2,3}));
    assert(test_diagonal_order({{1,4,5}}, {1,4,5}));
    assert(test_diagonal_order({{1,4,5},{6,7,9}}, {1,4,6,7,5,9}));
    assert(test_diagonal_order({{1,2},{4,5},{7,8}}, {1,2,4,7,5,8}));
    assert(test_diagonal_order({{1,2,3},{4,5,6},{7,8,9}}, {1,2,4,7,5,3,6,8,9}));
}

int main(int argc, char** argv) {
    test_diagonal_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
