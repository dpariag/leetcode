// Leetcode: https://leetcode.com/problems/house-robber/description/
// An array holds the amount of money at each house on a street. You wish to rob houses
// so as to maximize your haul, but you cannot rob adjacent houses. Find the max haul possible. 

// Brute Force: Generate all subsets of houses, eliminate those with adjacent houses, track max.
// Better: Use dynamic programming to either choose the i'th house or not. O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 2ms. Beats 38.10% of submissions, ties < 1% of submissions.
class Solution {
public:
    int rob(const std::vector<int>& nums) {
    	int prev1 = 0, prev2 = 0, cur = 0;
    	for (int i = 0; i < nums.size(); ++i) {
    		cur = std::max(prev1, nums[i] + prev2);
    		prev2 = prev1, prev1 = cur;
    	}
    	return cur;
    }
};

void test_robber() {
	Solution soln;

	assert(soln.rob({}) == 0);
	assert(soln.rob({4}) == 4);
	assert(soln.rob({10,2,15,5}) == 25); // 10+15
	assert(soln.rob({10,12,5,5}) == 17); // 12+5
	assert(soln.rob({5,12,5,5,10,1}) == 22); // 12+10
}

int main(int argc, char** argv) {
	test_robber();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
