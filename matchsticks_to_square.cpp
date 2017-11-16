// Leetcode: https://leetcode.com/problems/matchsticks-to-square/description/ 
// Given an array of numbers representing matchstick lengths, determine if you can construct
// a square using all the matchsticks. You may join matchsticks, but cannot break them.

// Brute Force: This is an instance of the partitioning problem. Note that *every* stick has to
// be used somewhere! If the array sum was small, we could
// use a table-driven approach similar to the knapsack problem. It's not so we use depth-first
// enumeration. For each number, try to place it on each of the four sides, then recurse.
// Better: Sort the numbers in descending order, so that large numbers get used up first.

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 149ms. Beats 27.00% of submissions, ties 0.25% of submissions.
class Solution {
public:
    bool build_square(const std::vector<int> sticks, int index, int sides[], int side_length) {
        if (index == sticks.size()) {
            // Have 3 sides and the sum is divisible by 4, no need to build 4th side.
            return sides[0] == side_length && sides[1] == side_length && sides[2] == side_length;
        }
        
        // Try to use sticks[index] in each of the 4 sides
        for (int i = 0; i < 4; ++i) {
            if (sides[i] + sticks[index] <= side_length) {
                sides[i] += sticks[index];
                if (build_square(sticks, index+1, sides, side_length)) { return true; }
                sides[i] -= sticks[index];
            }
        }
        return false;
    }

    bool makesquare(std::vector<int>& nums) {
        if (nums.empty()) { return false; }
        int sides[4] = {0,0,0,0};

        // Make sure the array sum is divisible by 4
        auto sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 4 != 0) { return false; }

        // Sort in descending order. Each stick belongs on a side, so place longer sticks first.
        std::sort(nums.begin(), nums.end(), [](int a, int b) { return a > b;});
        return build_square(nums, 0, sides, sum / 4);
    }
};

bool test_makes_square(std::vector<int> nums, bool expected) {
    Solution soln;
    return soln.makesquare(nums) == expected;
}

void test_makes_square() {
    assert(test_makes_square({2,2,2,2,2,6}, false));
    assert(test_makes_square({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}, true));
    assert(test_makes_square({1,1,2,2,2}, true));
    assert(test_makes_square({3,3,3,3,4},false));
    assert(test_makes_square({1,2,2,3,4,4}, true));
}

int main(int argc, char** argv) {
    test_makes_square();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
