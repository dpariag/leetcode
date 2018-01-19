// Leetcode: https://leetcode.com/problems/count-of-range-sum/description/
// Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
// RangeSum S(i, j) is the sum of nums[i..j] (i ≤ j), inclusive.

// Brute Force: Generate all subarrays and compare their sums to [lower,upper]. O(n^3)
// Better: Compute prefix sums of nums[0..i] and store them in a multiset as we iterate nums.
// For each sum, see if there is a stored prefix sum that brings us below (sum-upper).
// Count down successive elements as long as the sum is >= lower. O(n*logn)

#include <set>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <assert.h>

using PrefixSums = std::multiset<int64_t>; // PrefixSums

// Accepted. 31ms. Beats 41.11% of submissions, ties 1.48% of submissions.
class Solution {
public:
    int countRangeSum(std::vector<int>& nums, int lower, int upper) {
        PrefixSums prefix_sums;
        int64_t count = 0, sum = 0;

        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (lower <= sum && upper >= sum) {
                ++count;
            }

            auto below  = prefix_sums.lower_bound(sum-upper);
            while (below != prefix_sums.end()) {
                auto range_sum = (sum - *below);
                if (range_sum < lower) { break; } // too small
                if (lower <= range_sum && upper >= range_sum) {
                    ++count; 
                }
                ++below;
            }
            prefix_sums.emplace(sum);
        }
        return count;
    }
};

bool test_count_range_sum(std::vector<int> nums, int lower, int upper, int expected) {
    Solution soln;
    return (soln.countRangeSum(nums, lower, upper) == expected);
}

void test_count_range_sum() {
    assert(test_count_range_sum({1,1,1,1,1}, 3, 4, 5));
    assert(test_count_range_sum({5,-2,-1,6,-1}, 1, 3, 4));
    assert(test_count_range_sum({-3,1,2,-2,2,-1}, -3, -1, 7));
    assert(test_count_range_sum({5,-2,-1,6,-1}, 3, 8, 9)); // [0,0], [0,1], [0,4], [1,4], [2,3], [3,3], [0,4], [2,4], [2,5]
}

int main(int argc, char** argv) {
    test_count_range_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}