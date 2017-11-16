// Leetcode: https://leetcode.com/problems/perfect-squares/ 
// Given n > 0, find the least number of perfect squares (e.g., 1, 4, 9, 16, ...) which sum to n.
// Example: Given n = 12, return 3 (12 = 4 + 4 + 4); given n = 13, return 2 (13 = 4 + 9).

// Approach #1: Depth-first-search, pruning any path that is longer than the current minimum.
// Note: Breadth-first-search is guaranteed to find a "shortest path", but probably explores more
// sub-optimal paths in the process.

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cmath>

// Accepted. 93ms. Beats 81.08% of solutions and ties < 1% of submissions.
class Solution {
public:
    int numSquares(int n) {
        int64_t min = n;
        int to_square(std::sqrt(n));
        return dfs_search(n, n, 0, min, to_square);
    }
    
    int64_t dfs_search(int n, int remainder, int num_squares, 
                       int64_t& cur_min, int to_square) {
        if (remainder == 0) {
            return 0;
        } else if (num_squares >= cur_min) {
            return std::numeric_limits<int>::max() - 1;
        }

        int64_t min_ways = std::numeric_limits<int>::max();
        for (int i = to_square; i > 0; --i) {
            int square = i * i;
            if (remainder - square >= 0) {
                int64_t min = 1 + dfs_search(n, remainder-square, num_squares+1, cur_min, i);
                min_ways = std::min(min_ways, min);
            }
            if (remainder == n) {
                cur_min = std::min(cur_min, min_ways);
            }
        }
        return min_ways;
    }
};

void test_num_squares() {
    Solution soln;
    assert(soln.numSquares(1) == 1);
    assert(soln.numSquares(9) == 1);
    assert(soln.numSquares(19) == 3); // 19 = 9 + 9 + 1
    assert(soln.numSquares(20) == 2); // 20 = 16 + 4 
    assert(soln.numSquares(10) == 2); // 10 = 9 + 1
    assert(soln.numSquares(22) == 3); // 22 = 9 + 9 + 4
    assert(soln.numSquares(35) == 3); // 35 = 25 + 9 + 1
    assert(soln.numSquares(9732) == 3); // 9732 = (98*98) + (11*11) +  
    assert(soln.numSquares(6337) == 2); // 9732 = (98*98) + (11*11) +  
    assert(soln.numSquares(1535) == 4); // 9732 = (98*98) + (11*11) +  
}

int main(int argc, char** argv) {
    test_num_squares();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
