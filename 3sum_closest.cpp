// Leetcode: https://leetcode.com/problems/3sum-closest/
// Given an integer array S, find three entries in S such that their sum is closest to a target i
// number. Return the sum of the three integers. Assume exactly one solution exists.
// Example: Given S = {-1 2 1 -4}, and target = 1, return 2 (-1 + 2 + 1 = 2).

// Brute Force: Generate all n choose 3 triples, calculate sums and record the min. O(n^3) time.
// Better: Sort the array. For each S[i], scan the subarray S[i+1...n] from either end,
// looking for the triple S[i] + S[left] + S[right] that has the closest sum to the target.
// O(n^2) time and O(1) space.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 13ms. Beats 60.40% of submissions, and ties 21.13% of submissions.
class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        assert(nums.size() >= 3);
        std::sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < nums.size(); ++i) {
            int left = i+1, right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (std::abs(sum - target) < std::abs(closest - target)) {
                    closest = sum;
                }
                if (sum < target) {
                    ++left;
                } else if (sum > target) {
                    --right;
                } else {
                    // sum == target, can't get any closer
                    return sum;
                }
            }
        }
        return closest;
    }
};

bool test_closest(std::vector<int> nums, int target, int closest) {
    Solution soln;
    return soln.threeSumClosest(nums, target) == closest;
}

void test_three_sum_closest() {
    assert(test_closest({-1, 2, 1, -4}, 1, 2));
    assert(test_closest({-1, 2, 1, -4}, 2, 2));
    assert(test_closest({-1, 2, 1, -4}, -4, -4));
    assert(test_closest({-1, 2, 1, -4}, -10, -4));
    assert(test_closest({-1, 2, 1, -4}, -1, -1));
    assert(test_closest({1, 1, 1, 1}, -1, 3));
    assert(test_closest({1, 1, 1, 1}, 3, 3));
}

int main(int argc, char** argv) {
    test_three_sum_closest();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
