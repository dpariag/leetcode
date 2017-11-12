// Leetcode: https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description/
// Given a non-empty integer array, find the min # of moves to make all elements equal, 
// where a move is incrementing or decrementing a selected element by 1.

// Approach: To minimize the number of moves, we try to move each element towards the median.
// This guarantees that 1/2 the elements move up, and 1/2 move down. Also, the # of moves
// is guaranteed minimal because any other choice of target would be further for 1/2 the elements.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 16ms. Beats 49.31% of submissions, ties 41.94% of submissions.
class Solution {
public:
    int minMoves2(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int median = nums[nums.size() / 2];

        int moves = 0;
        for (int i = 0; i < nums.size(); ++i) {
            moves += std::abs(nums[i] - median); 
        }
        return moves;
    }
};

bool test_min_moves2(std::vector<int> nums, int expected_moves) {
    Solution soln;
    return soln.minMoves2(nums) == expected_moves;
}

void test_min_moves2() {
    assert(test_min_moves2({11}, 0));
    assert(test_min_moves2({11,11,11}, 0));
    assert(test_min_moves2({11,11,11,11}, 0));
    assert(test_min_moves2({1,2,3,4,5}, 6));
    assert(test_min_moves2({1,1,3,3,3}, 4));
    assert(test_min_moves2({3,3,3,1,1}, 4));
    assert(test_min_moves2({1,10,15,18,30,32}, 54));
}

int main(int argc, char** argv) {
    test_min_moves2();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
