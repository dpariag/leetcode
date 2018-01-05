// Leetcode: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
// Given an array of positive integers, find 3 non-overlapping subarrays of size k with maximum sum.

// Brute Force: Generate all combos of 3 non-overlapping subarrays of size k, track max. O(k*n^3)
// Better: Build tables that contain: 
// 1) Sum of subarray of size k ending at index i
// 2) Largest subarray of size k seen over [0...i]
// 3) Largest subarray of size k seen over [i...end]
// These tables can be built in O(n) time, then iterated in O(n) time to find 3 arrays with max sum.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

static const int MIN_INT = std::numeric_limits<int>::min();

struct SubArray {
    int sum = MIN_INT;  // Sum of subarray elements
    int index = -1;     // Starting index of subarray
};

// Accepted. 32ms. Beats 74.47% of submissions, ties 13.77% of submissions.
class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        std::vector<int> sums(nums.size(), 0);
        std::vector<SubArray> left_max(nums.size());  // max subarray over 0..i
        std::vector<SubArray> right_max(nums.size()); // max subarray over i..end

        // Sweep right to left building right_max
        int sum = 0, max = MIN_INT, index = -1;
        for (int i = nums.size()-1; i >=0; --i) {
            sum += nums[i];
            if (i < (nums.size() - k)) { sum -= nums[i+k]; }
            if (sum >= max) { index = i, max = sum; } // prefer leftmost max
            if (i <= (nums.size()-k)) { right_max[i] = {max,index}; }
        }

        // Sweep left to right building left max and sums
        sum = 0, max = MIN_INT, index = -1;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (i >= k) { sum -= nums[i-k]; }
            if (sum > max) { index = i-k+1, max = sum; }
            if (i >= k-1) {
                sums[i] = sum;
                left_max[i] = {max, index};
            }
        }
  
        sum = 0, max = MIN_INT;
        int first = -1, second = -1, third = -1;
        for (int i = k; i <= nums.size() - (2*k); ++i) {
            sum = sums[i+k-1] + left_max[i-1].sum + right_max[i+k].sum;
            if (sum > max) {
                first = left_max[i-1].index, second = i, third = right_max[i+k].index;
                max = sum;
            }
        }
        return {first, second, third};
    }
};

bool test_max_sum(std::vector<int> nums, int k, std::vector<int> expected) {
    Solution soln;
    return soln.maxSumOfThreeSubarrays(nums,k) == expected;
}

void test_max_sum() {
    assert(test_max_sum({7,13,20,19,19,2,10,1,1,19}, 3, {1,4,7}));
    assert(test_max_sum({1,2,1,2,6,7,5,1}, 2, {0,3,5}));
    assert(test_max_sum({10,5,1,8,10,20,5,10}, 2, {0,4,6}));    
}

int main(int argc, char** argv) {
    test_max_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
