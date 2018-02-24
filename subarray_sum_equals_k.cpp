// Leetcode: https://leetcode.com/problems/subarray-sum-equals-k/description/
// Given an array of integers, find the total number of continuous subarrays whose sum equals to k.

// Brute Force: Generate all subarrays, count those which sum to k. O(n^3) time.
// Better: Count prefix sums in a hash map, then scan the array counting prefix sums that allow
// a subarray sum of k. O(n) time and space

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using PrefixSumCount = std::unordered_map<int, int>; // prefix sum -> it's count

// Accepted. 29ms. Beats 86.94% of submissions, ties 10.28% of submissions.
class Solution {
public:
    int subarraySum(const std::vector<int>& nums, int k) {
        PrefixSumCount prefix_sums;
        int count = 0, sum = 0;

        prefix_sums[0] = 1; // empty array
        for (int i = 0; i < nums.size(); ++i)  {
            sum += nums[i];
            auto found = prefix_sums.find(sum-k); // sum - v = k
            if (found != prefix_sums.end()) {
                count += found->second;
            }
            prefix_sums[sum]++;
        }
        return count;
    }
};

void test_subarray_sum() {
    Solution soln;

    assert(soln.subarraySum({1,0,10,0,5}, 10) == 4);
    assert(soln.subarraySum({1,0,10,0,5}, 15) == 2);
    assert(soln.subarraySum({1,0,10,0,5}, 16) == 1);
    assert(soln.subarraySum({0,0,0,0}, 0) == 10);
    assert(soln.subarraySum({-1,-2,-3,-4}, -3) == 2);
}

int main(int argc, char** argv) {
    test_subarray_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
