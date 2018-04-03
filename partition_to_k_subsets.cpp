// Leetcode: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/description/
// Given an integer array, nums, and an integer k (k > 0), determine if nums can be 
// partitioned into k non-empty subsets with equal sums.

// Brute Force: Generate all possible subsets, sort by sum and look for k subsets with equal sum.
// Better: Recursion with backtracking. Try adding each number to each sum in turn, backtracking
// if necessary.

#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 48ms. Beats 22.44% of submissions.
class Solution {
public:
    bool can_partition(std::vector<int>& nums, std::vector<int>& sums, int index, int desired_sum) {
        if (index == nums.size()) {
             for (int i = 0; i < sums.size(); ++i) {
                if (sums[i] != desired_sum) return false;
            }
            return true;
        }

        for (int i = 0; i < sums.size(); ++i) {
            if (sums[i] + nums[index] <= desired_sum) {
                sums[i] += nums[index];
                if (can_partition(nums, sums, index+1, desired_sum)) { return true; }
                sums[i] -= nums[index];
            }
        }
        return false;
    }

    bool canPartitionKSubsets(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end(), [](int i, int j) {return i > j;});
        auto sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) { return false; }
        std::vector<int> sums(k, 0);
        return can_partition(nums, sums, 0, sum/k);
    }
};

bool test_can_partition(std::vector<int> nums, int k, bool expected) {
    Solution soln;
    return soln.canPartitionKSubsets(nums, k) == expected;
}

void test_can_partition() {
    assert(test_can_partition({4, 3, 2, 3, 5, 2, 1}, 4, true));
    assert(test_can_partition({5, 3, 2, 3, 5, 2, 1}, 4, false));
    assert(test_can_partition({4, 4, 4, 4, 4, 4, 4}, 4, false));
    assert(test_can_partition({4, 4, 4, 4, 4, 4, 4}, 7, true));
    assert(test_can_partition({4, 5, 4, 5, 4, 5}, 3, true));
}


int main(int argc, char** argv) {
    test_can_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}