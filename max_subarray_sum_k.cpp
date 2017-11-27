// Leetcode: https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/description/
// Given an integer array and a target value k, find the largest subarray with sum k. 
// Return 0 if none exists.

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Sums = std::unordered_map<int, int>; // map sum -> earliest subarray with that sum.

// Accepted. Beats 75.43% of submissions, ties 14.43% of submissions.
class Solution {
public:
    int maxSubArrayLen(const std::vector<int>& nums, int k) {
        Sums sums;
        sums.emplace(0, -1);
        int cur_sum = 0, max_length = 0;
        for (int i = 0; i < nums.size(); ++i) {
            cur_sum += nums[i];
            int target = cur_sum - k;
            auto found = sums.find(target); 
            if (found != sums.end()) {
                max_length = std::max(max_length, i - found->second);
            }
            if (!sums.count(cur_sum)) { 
                sums.emplace(cur_sum, i); 
            }
        }
        return max_length;
    }
};

void test_max_subarray() {
    Solution soln;

    assert(soln.maxSubArrayLen({-2,-1,2,1}, 1) == 2);
    assert(soln.maxSubArrayLen({1,2,3,4}, 0) == 0);
    assert(soln.maxSubArrayLen({1,2,3,4}, 3) == 2);
    assert(soln.maxSubArrayLen({1,2,3,4}, 6) == 3);
    assert(soln.maxSubArrayLen({1,2,3,4}, 10) == 4);
    assert(soln.maxSubArrayLen({1,2,3,4}, 11) == 0);
    assert(soln.maxSubArrayLen({1,-1,5,-2,3}, 3) == 4);
}

int main(int argc, char** argv) {
    test_max_subarray();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
