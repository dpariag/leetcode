// Leetcode: https://leetcode.com/problems/rotate-image/description/
// Given an NxN matrix representing an image, rotate it by 90 degrees clockwise.

// Brute Force: Allocate a second matrix, copy the i'th row into the (num_cols - i - 1)'th column.
// Better: Rotate the array in place. Each element is placed in its target position, after saving
// the target. Next place the target, saving the target's target etc. 4 rotations complete the sequence.

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. Beats 37.22% of submissions, ties 62.78% of submissions.
class Solution {
public:
    void rotate(Matrix& matrix) {
        for (int row = 0; row < int(matrix.size()) / 2; ++row) {
            const int num_cols = matrix[0].size();
            for (int col = row; col < matrix[0].size() - row - 1; ++col) {
                // Perform 4 moves
                int src_row = row, src_col = col;
                int src_value = matrix[src_row][src_col];
                for (int i = 0; i < 4; ++i) {
                    int dest_row = src_col, dest_col = num_cols - src_row - 1;
                    int dest_value = matrix[dest_row][dest_col];
                    matrix[dest_row][dest_col] = src_value; 
                    src_row = dest_row, src_col = dest_col;
                    src_value = dest_value;
                }
            }
        }
    }
};

bool test_rotate(Matrix matrix, Matrix rotated) {
    Solution soln;
    soln.rotate(matrix);
    return matrix == rotated;
}

void test_rotate() {
    assert(test_rotate({{0}}, {{0}}));
    assert(test_rotate({{0,1},{2,3}}, {{2,0}, {3,1}}));
    assert(test_rotate({{1,2,3},{4,5,6},{7,8,9}}, {{7,4,1}, {8,5,2},{9,6,3}}));
    assert(test_rotate({{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}, 
                       {{13,9,5,1}, {14,10,6,2},{15,11,7,3},{16,12,8,4}}));
}

int main(int argc, char** argv) {
    test_rotate();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
