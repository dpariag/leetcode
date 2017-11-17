// Leetcode: https://leetcode.com/problems/subarray-product-less-than-k/description/
// Given a non-empty array of positive integers, count the number of subarrays whose product is 
// less than k.

// Brute Force: Generate all subarrays and compute their product. O(n^3) time.
// Better: Use a sliding window over the array, enlarge if product < k, shrink if product >= k.
// O(n) time and O(1) space.

#include <vector>
#include <numeric>
#include <iostream>
#include <assert.h>

// Accepted. 135ms. Beats 47.67% of submissions, ties 3.76% of submissions.
class Solution {
public:
    int numSubarrayProductLessThanK(const std::vector<int>& nums, int k) {
        int product = 1, count = 0;
        int left = 0, right = 0;
        while (right < nums.size()) {
            product *= nums[right];
            while (left <= right && product >= k) {
                product /= nums[left++];
            }
            count += (right - left + 1);
            ++right;
        }
        return count;
    }
};

void test_subarray_sums() {
    Solution soln;
    
    assert(soln.numSubarrayProductLessThanK({5,10,5,10}, 5) == 0);
    assert(soln.numSubarrayProductLessThanK({10,5,2,6}, 100) == 8);
    assert(soln.numSubarrayProductLessThanK({5,10,5,10}, 1000) == 9);
    assert(soln.numSubarrayProductLessThanK({5,10,5,10}, 6) == 2);
    assert(soln.numSubarrayProductLessThanK({5,1,1,10}, 2) == 3);
    assert(soln.numSubarrayProductLessThanK({1,1,1,1}, 2) == 10);
    assert(soln.numSubarrayProductLessThanK({1,1,1,1}, 1) == 0);
    assert(soln.numSubarrayProductLessThanK({1,1,10,10}, 2) == 3);
}

int main(int argc, char** argv) {
    test_subarray_sums();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
