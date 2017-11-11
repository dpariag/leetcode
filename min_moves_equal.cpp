// Leetcode: https://leetcode.com/problems/minimum-moves-to-equal-array-elements/description/
// Given a non-empty integer array, find the min # of moves required to make all array elements 
// equal, where a move is incrementing (n-1) elements by 1.

// Brute Force: Repeatedly increment (n-1) elements until all equal. O(largest elem * n)
// Better: Calculate min and max. The spread is (max-min) and it defines how much the min
// element must be incremented by. Sweep array looking at how much each elem would surpass the max
// by given the spread. Increment the number of moves. 

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 49ms. Beats 74.62% of submissions, ties 22.92% of submissions.
class Solution {
public:
    int minMoves(const std::vector<int>& nums) {
        int max = std::numeric_limits<int>::min();
        int min = std::numeric_limits<int>::max();

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > max) { max = nums[i]; }
            if (nums[i] < min) { min = nums[i]; }
        }
       
        int moves = 0; 
        int spread = (max - min); 
        for (int i = 0; i < nums.size(); ++i) {
            moves += ((nums[i] + spread) - max);
        }
        return moves;
    }
};

void test_min_moves() {
    Solution soln;

    assert(soln.minMoves({3,3,3}) == 0);
    assert(soln.minMoves({3,3,4}) == 1);
    assert(soln.minMoves({1,2,3}) == 3);
    assert(soln.minMoves({1,2,3,4}) == 6);
    assert(soln.minMoves({3,4,6}) == 4);
    assert(soln.minMoves({3,4,7}) == 5);
    assert(soln.minMoves({3,4,4,8}) == 7);
    assert(soln.minMoves({4,6,6,8}) == 8);
}

int main(int argc, char** argv) {
    test_min_moves();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
