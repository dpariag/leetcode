// Leetcode: https://leetcode.com/problems/3sum-smaller/description/
// Given an integer array, nums, and a target, find the number of triplets i, j, k 
// with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 36.01% of submissions, ties 63.99% of submissions.
class Solution {
public:
    int threeSumSmaller(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int i = 0, j = 1, k = (nums.size() - 1), sz = nums.size();
        int count = 0;
        while (j < sz) {
            i = 0, k = sz - 1;
            while (i < j) {
                while (k > j && (nums[i] + nums[j] + nums[k] >= target)) { --k; }
                if (k > j) { count += (k - j); }
                ++i;
            }
            ++j;
        }
        return count;
    }
};

bool test_smaller(std::vector<int> nums, int target, int expected) {
    Solution soln;
    return soln.threeSumSmaller(nums, target) == expected;
}

void test_smaller() {
    assert(test_smaller({1,1,-2}, 1, 1)); // -2, 1, 1
    assert(test_smaller({-2,0,1,3}, 2, 2));
    assert(test_smaller({1,2,5,6,12,15}, 20, 9));
    assert(test_smaller({2,1,6,5,15,12}, 20, 9));
}

int main(int argc, char** argv) {
    test_smaller();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
