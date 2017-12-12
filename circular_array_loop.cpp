// Leetcode: https://leetcode.com/problems/circular-array-loop/description/
// Iterate an array, jumping A[i] spots forwards or backwards from index i.
// Determine if the array has a uni-directional loop of length > 1

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 27.55% of submissions, ties 72.45% of submissions.
class Solution {
public:
    bool circularArrayLoop(std::vector<int>& nums) {
        if (nums.empty()) { return false; }

        int visited = 0, cur = 0;
        bool forward = nums[0] > 0;
        while (visited < nums.size()) {
            int next = (cur + nums[cur]) % nums.size();
            if (next == cur) { ++cur; continue; } // self loop (too short)
            if (nums[next] == 0) { return true; } // already visited
            if ((forward && nums[next] < 0) || (!forward && nums[next] > 0) ) { 
                // Direction change
                return false; 
            }
            nums[cur] = 0;
            ++visited;
            cur = next;
        }
        return false;
    }
};

bool test_array_loop(std::vector<int> nums, bool expected) {
    Solution soln;
    return soln.circularArrayLoop(nums) == expected;
}

void test_array_loop() {
    assert(test_array_loop({-2,1,-1,-2,-2}, false));
    assert(test_array_loop({2,-1,1,2,2}, true));
    assert(test_array_loop({-1,2}, false));
    assert(test_array_loop({1}, false));
    assert(test_array_loop({3,1,-2,-2}, false));
    assert(test_array_loop({3,1,2}, true));

}

int main(int argc, char** argv) {
    test_array_loop();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
