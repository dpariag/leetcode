// Leetcode: https://leetcode.com/problems/search-a-2d-matrix/description/
// Write an efficient algorithm that searches for a value in an m x n matrix with the following properties:
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.

// Brute Force: Scan the matrix row by row looking for the target. O(m*n) time.
// Better: Use binary search to find the correct row, then binary search that row. O(logm + logn) time.

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 13ms. Beats 48.06% of submissions, ties 29.81% of submissions.
class Solution {
public:

    bool searchRow(const std::vector<int>& row, int target) {
        int start = 0, end = row.size() - 1;

        while (start <= end) {
            int mid = start + (end-start) / 2;
            if (target == row[mid]) {
                return true;
            } else if (target < row[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return false;
    }

    bool searchMatrix(Matrix& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) { return false; }

        int top = 0, bottom = matrix.size()-1, row = -1;
        while (top <= bottom) {
            int mid = top + (bottom - top) / 2;
            if (target >= matrix[mid].front() && target <= matrix[mid].back()) {
                row = mid;
                break;
            } else if (target < matrix[mid].front()) {
                bottom = mid -1;
            } else if (target > matrix[mid].back()) {
                top = mid + 1;
            }
        }

        if (row != -1) {
            return searchRow(matrix[row], target);
        }
        return false;
    }
};

bool test_search_matrix(Matrix m, int target, bool expected) {
    Solution soln;
    return soln.searchMatrix(m, target) == expected;
}

void test_search_matrix() {
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 1, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 2, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 3, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 4, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 5, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 6, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 7, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 8, true));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 9, true));

    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 0, false));
    assert(test_search_matrix({{1,2,3},{4,5,6},{7,8,9}}, 11, false));

}

int main(int argc, char** argv) {
    test_search_matrix();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}