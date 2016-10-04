// Leetcode: https://leetcode.com/problems/jump-game/
// Given an array of non-negative integers, where each element a max jump from that position,
// determine if you are able to start at the first index and reach the last index.
// Example: Given {2,3,1,1,4}, return true. Given {3,2,1,0,4}, return false

// Brute Force: Recursive evaluation of all jumps, with exponential runtime.
// Better: Iterate the array, calculating the maximum reach possible using nums[0]..nums[i]
// Return true if max reach includes the last element. O(n) time and O(1) space.
#include <vector>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. Runtime 13ms. Beats 43.73% of submissions and ties 40.55% of submissions
class Solution {
public:
    bool canJump(Numbers& nums) {
        if (nums.empty()) { return true; }
        int i = 0, reach = nums.front(), last = nums.size() - 1;
       
        while (i <= reach && reach < last) {
            reach = std::max(reach, i + nums[i]);
            ++i;
        } 
        return (reach >= last);
    }
};

bool test_jump(Numbers nums, bool expected) {
    Solution soln;
    return soln.canJump(nums) == expected;
}

void test_can_jump() {
    assert(test_jump({1}, true));
    assert(test_jump({0,0,0,0}, false));
    assert(test_jump({2,3,1,1,4}, true));
    assert(test_jump({3,2,1,0,4}, false));
    assert(test_jump({0,2,1,1,4}, false));
    assert(test_jump({1,2,1,1,4}, true));
    assert(test_jump({1,0,1,1,4}, false));
    assert(test_jump({11,0,0,0,0}, true));
    assert(test_jump({11,0,0,0,0,0,0,0,0,0,0,0,0}, false));
    assert(test_jump({11,0,0,0,0,0,0,0,0,0,0,1,0}, true));
}

int main(int argc, char** argv) {
    test_can_jump();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
