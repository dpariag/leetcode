// Leetcode: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
// Given an array of positive integers, find three non-overlapping subarrays of size k with maximum 
// sum.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

static const int MIN_INT = std::numeric_limits<int>::min();

struct SubArray {
    int sum = MIN_INT;  // Sum of subarray elements
    int index = -1;     // Starting index of subarray
};

void print(std::vector<SubArray>& s) {
    for (auto item : s) {
        std::cout << "{sum = " << item.sum << ", index = " << item.index << "} " << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        std::vector<int> sums(nums.size(), 0);
        std::vector<SubArray> left_max(nums.size());  // max subarray over 0..i
        std::vector<SubArray> right_max(nums.size()); // max subarray over i..end

        int sum = 0, max = MIN_INT, index = -1;
        for (int i = nums.size()-1; i >=0; --i) {
            sum += nums[i];
            if (i < (nums.size() - k)) {
                sum -= nums[i+k];
            }
            if (sum >= max) { // prefer left maxes
                index = i, max = sum;
            }
            if (i <= (nums.size()-k)) {
                right_max[i] = {max,index};
            }
        }

        sum = 0, max = MIN_INT, index = -1;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (i >= k) {
                sum -= nums[i-k];
            }
            if (sum > max) {
                index = i-k+1, max = sum;
            }
            if (i >= k-1) {
                sums[i] = sum;
                left_max[i] = {max, index};
            }
        }
        print(left_max);
        print(right_max);

        sum = 0, max = MIN_INT;
        int first = -1, second = -1, third = -1;
        for (int i = k; i <= nums.size() - (2*k); ++i) {
            sum = sums[i+k-1] + left_max[i-k].sum + right_max[i+k].sum;
            if (sum > max) {
                first = left_max[i-k].index, second = i, third = right_max[i+k].index;
            }
        }
        std::cout << first << "," << second << "," << third << std::endl;
        return {first, second, third};
    }
};

bool test_max_sum(std::vector<int> nums, int k, std::vector<int> expected) {
    Solution soln;
    return soln.maxSumOfThreeSubarrays(nums,k) == expected;
}

void test_max_sum() {
    assert(test_max_sum({10,5,1,8,10,20,5,10}, 2, {0,4,6}));
}

int main(int argc, char** argv) {
    test_max_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
