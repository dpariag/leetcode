// Leetcode: https://leetcode.com/problems/contiguous-array/description/
// Given a binary array, find the max length of a contiguous subarray with equal number of 0 and 1.

// Brute Force: Generate all subarrays, check each for equal numbers of 0s and 1s. O(n^3) time.
// Better: Scan the array, using a hash map to track prefixes which can be "subtracted" 
// from the current subarray to yield a balanced one. O(n) time and space.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using SubArrays = std::unordered_map<int, int>; // (NumZeros - NumOnes) --> last index of subarray

// Accepted. 119ms. Beats 94.86% of submissions, ties < 1% of submissions.
class Solution {
public:
    int findMaxLength(std::vector<int>& nums) {
        SubArrays subarrays;
        int num_ones = 0, num_zeros = 0;
        int longest = 0;
       
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) { ++num_zeros; } 
            else { ++num_ones; }

            if (num_zeros == num_ones) {
                longest = i + 1;
            } else {
                auto found = subarrays.find(num_zeros-num_ones); 
                if (found != subarrays.end()) {
                    longest = std::max(longest, (i+1) - found->second);
                } else {
                    subarrays.emplace((num_zeros-num_ones), i+1);
                }
            }
        }
        return longest;
    }
};

bool test_max_length(std::vector<int> nums, int expected_length) {
    Solution soln;
    return soln.findMaxLength(nums) == expected_length;
}

void test_max_length() {
    assert(test_max_length({}, 0));
    assert(test_max_length({1}, 0));
    assert(test_max_length({1,0}, 2));
    assert(test_max_length({1,0,1}, 2));
    assert(test_max_length({1,0,1,1,0}, 4));
    assert(test_max_length({1,1,1,0,0}, 4));
    assert(test_max_length({0,0,1,1,1}, 4));
    assert(test_max_length({0,0,0,1,1,1}, 6));
}

int main(int argc, char** argv) {
    test_max_length();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
