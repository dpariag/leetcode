// Leetcode: https://leetcode.com/problems/house-robber-ii/description/
// Repeat the house robber problem, but this time the houses are arranged in a circle,
// meaning that the first and last houses are adjacent.

// Approach: Reuse the solution to the house robber problem, but perform 2 passes.
// The first pass omits the first house, the second pass omits the last house.
// Return the larger result.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 2ms. Beats 41.69% of submissions, ties < 1% of submissions.
class Solution {
public:
    int rob(const std::vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums.front();
        int prev2 = 0, prev1 = 0, cur = 0;

        // Omit the first house
        for (int i = 1; i < nums.size(); ++i) {
            cur = std::max(prev1, nums[i]+prev2);
            prev2 = prev1, prev1 = cur;
        }

        int first_pass = cur;
        prev2 = 0, prev1 = 0, cur = 0;
        
        // Omit the last house
        for (int i = 0; i < int(nums.size())-1; ++i) {
            cur = std::max(prev1, nums[i]+prev2);
            prev2 = prev1, prev1 = cur;
        }
        return std::max(first_pass, cur);
    }
};

void test_rob() {
    Solution soln;

    assert(soln.rob({}) == 0);
    assert(soln.rob({10}) == 10);
    assert(soln.rob({7,10}) == 10);
    assert(soln.rob({7,10,5}) == 10);
    assert(soln.rob({1,1,1}) == 1);
    assert(soln.rob({10,2,15,5}) == 25);
    assert(soln.rob({10,12,5,5}) == 17);
    assert(soln.rob({5,12,5,5,10,15}) == 32);
}

int main(int argc, char** argv) {
    test_rob();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}