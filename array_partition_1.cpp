// Leetcode: https://leetcode.com/problems/array-partition-i/description/ 
// Given an array of 2n integers, group entries into n pairs (a1, b1), (a2, b2), ..., (an, bn) 
// such that sum of min(ai, bi) for all i 1..n is maximized.

// Brute Force: Generate all pairs of integers, then evaluate all permutations. O(n!) time.
// Better: Sort the array, and sum even-numbered indices. O(n*logn) time.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 79ms. Beats 59.35% of submissions, ties 23.40% of submissions.
class Solution {
public:
    int arrayPairSum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        for (int i = 0; i < nums.size(); i+=2) {
            sum += nums[i];
        }
        return sum;
    }
};

bool test_array_pair_sum(std::vector<int> nums, int expected_sum) {
    Solution soln;
    auto sum = soln.arrayPairSum(nums);
    return sum == expected_sum;
}

void test_array_pair_sum() {
    assert(test_array_pair_sum({1,4}, 1));
    assert(test_array_pair_sum({1,4,3,2}, 4));
    assert(test_array_pair_sum({1,4,3,2,6,10}, 10));
}

int main(int argc, char** argv) {
    test_array_pair_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
