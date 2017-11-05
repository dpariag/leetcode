// Leetcode: https://leetcode.com/problems/range-addition-ii/description/
// You are given an MxN matrix, and a sequence of operations of the form (a,b). Each operation
// indicates that the sub-matrix [0,0 -> a,b] should be incremented by 1. Return the number of
// elements holding the max. value in the matrix.

// Brute Force: Build the matrix, perform operations, count max elements. O(n^3) time, O(n^2) space.
// Better: Track the intersection of sub-matrices specified by each operation. O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 73.77% of submissions, ties 26.23% of submissions.
class Solution {
public:
    int maxCount(int m, int n, const std::vector<std::vector<int>>& ops) {
        int min_row = m, min_col = n;
        for (const auto& op : ops) {
            min_row = std::min(min_row, op[0]);
            min_col = std::min(min_col, op[1]);
        }
        return min_row * min_col;
    }
};

void test_max_count() {
    Solution soln;

    assert(soln.maxCount(3,3, {{2,2}, {3,3}}) == 4);
    assert(soln.maxCount(1,1, {{1,1}, {1,1}}) == 1);
    assert(soln.maxCount(5,1, {{4,1}, {1,1}}) == 1);
}

int main(int argc, char** argv) {
    test_max_count();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
