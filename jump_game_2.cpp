// Leetcode: https://leetcode.com/problems/jump-game-ii/
// Given an array of non-negative integers, where each element is the max jump from that position,
// Find the minimum number of jumps, required to go from start to finish (which is always possible)
// Example: given A = [2,3,1,1,4], return 2. (0->1, 1->4) 

// Brute Force: Recursive enumeration of all paths forward. Exponential runtime.
// Better: Iterate the vector, tracking the furthest we can jump, and also the min number of hops.
// O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. Runtime 13ms. Beats 56.14% of submissions, ties 32.57% of submissions.
class Solution {
public:
    int jump(std::vector<int>& nums) {
        if (nums.size() <= 1) { return 0; }

        int furthest = nums[0], num_hops = 1; // Furthest reachable index, and number of hops reqd
        int current_reach = furthest;

        for (auto i = 1; i < nums.size() && current_reach < nums.size() - 1; ++i) {
            if (i + nums[i] > furthest) {
                furthest = i + nums[i];
            }
            if (i >= current_reach) {
                ++num_hops;
                current_reach = furthest;
            } 
        }
        return num_hops;
    }
};

bool test_min_jumps(std::vector<int> nums, int expected_min_hops) {
    Solution soln;
    return soln.jump(nums) == expected_min_hops;
}

void test_min_jumps() {
    assert(test_min_jumps({}, 0));
    assert(test_min_jumps({0}, 0));
    assert(test_min_jumps({2,1}, 1));
    assert(test_min_jumps({2,3,1,1,4}, 2));
    assert(test_min_jumps({2,0,1,1,4}, 3));
    assert(test_min_jumps({7,0,1,1,4,0,0,0}, 1));
    assert(test_min_jumps({1,2,4,1,0,0,1,0}, 4));
    assert(test_min_jumps({7,2,6,1,0,0,1,0,1}, 2));
    assert(test_min_jumps({7,0,6,1,0,0,1,0,1}, 2));
    assert(test_min_jumps({7,0,6,1,0,0,1,0,1}, 2));
    assert(test_min_jumps({3,0,5,5,0,0,1,0,1}, 2));
    assert(test_min_jumps({3,0,3,1,0,3,1,0,1}, 3));
    assert(test_min_jumps({3,3,5,0,3,1,0,1}, 2));
    assert(test_min_jumps({3,3,5,0,0,1,0,1}, 2));
    assert(test_min_jumps({1,3,5,0,0,1,0,1}, 3));
}

int main(int argc, char** argv) {
    test_min_jumps();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
