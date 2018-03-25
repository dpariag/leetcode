// Leetcode: https://leetcode.com/problems/search-a-2d-matrix-ii/description/

// Brute Force: Scan the matrix row by row looking for target.
// Better: Divide the matrix into 4 quadrants and perform a 4-way binary search in each one.
// Better: Start at the top-right value. Move left if the target is smaller, 
// or down if the target is larger. O(m+n) time.

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 73ms. Beats 38.65% of submissions, ties 1.05% of submissions.
class Solution {
public:
    bool searchMatrix(const Matrix& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) { return false; }

        int row = 0, col = matrix[0].size() - 1;
        while (row < matrix.size() && col >= 0) {
            if (target == matrix[row][col]) {
                return true; 
            } else if (target < matrix[row][col]) {
                --col;
            } else { 
                ++row;
            }
        }
        return false;
    }
};

void test_search_matrix() {
    Solution soln;
    Matrix m({{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}});

    assert(soln.searchMatrix(m, 1) == true);
    assert(soln.searchMatrix(m, 15) == true);
    assert(soln.searchMatrix(m, 8) == true);
    assert(soln.searchMatrix(m, 9) == true);
    assert(soln.searchMatrix(m, 17) == true);
    assert(soln.searchMatrix(m, 23) == true);
    assert(soln.searchMatrix(m, 30) == true);
    assert(soln.searchMatrix(m, 100) == false);
    assert(soln.searchMatrix(m, -1) == false);
    assert(soln.searchMatrix(m, 28) == false);
    assert(soln.searchMatrix(m, 31) == false);

    assert(soln.searchMatrix({{}}, 1) == false);
    assert(soln.searchMatrix({}, 1) == false);
}

int main(int argc, char** argv) {
    test_search_matrix();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}