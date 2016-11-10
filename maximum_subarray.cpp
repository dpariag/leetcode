// Leetcode: https://leetcode.com/problems/maximum-subarray/
// Find the non-empty, contiguous, subarray which has the largest sum.
// Example: Given the array [-2,1,-3,4,-1,2,1,-5,4], the subarray [4,-1,2,1] has the largest sum (6).

// Brute Force: Generate all O(n^2) subarrays, compute sums, and track max. O(n^3) time, O(1) space.
// Better: Calculate the running sum over the array. If running sum of nums[i..j] becomes negative, 
// then reset sum to zero, discarding the subarray nums[i..j]. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 9ms. Beats 34.95% of submissions and ties 64.47% of submissions.
class Solution {
public:
    int maxSubArray(Numbers& nums) {
        int sum = 0, max_sum = std::numeric_limits<int>::min();
        for (auto n : nums) {
            sum += n;
            max_sum = std::max(max_sum, sum);
            sum = std::max(sum, 0);
        }
        return max_sum;
    }
};

bool test_max_subarray(const Numbers& nums, int expected_max) {
    Solution soln;
    Numbers copy(nums);
    return soln.maxSubArray(copy) == expected_max;
}

void test_max_subarray() {
    assert(test_max_subarray({0}, 0));
    assert(test_max_subarray({0,1,10,8}, 19));
    assert(test_max_subarray({-1,1,10,8}, 19));
    assert(test_max_subarray({-1,-1,0,-19,5}, 5));
    assert(test_max_subarray({-1,-1,0,-19,5,1,10}, 16));
    assert(test_max_subarray({-1,-1,0,-19,5,1,10,0}, 16));
    assert(test_max_subarray({-1,-1,0,-19,5,1,10,0,-50,100}, 100));
    assert(test_max_subarray({-1,-1,0,-19,5,1,10,0,-5,100}, 111));
    assert(test_max_subarray({-1,-1,0,-19,5,1,10,0,-1,-11}, 16));
    assert(test_max_subarray({-10,-11,-5,-6,-100}, -5));
    assert(test_max_subarray({-2,1,-3,4,-1,2,1,-5,4}, 6));
}

int main(int argc, char** argv) {
    test_max_subarray();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
