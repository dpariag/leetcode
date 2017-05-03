// Leetcode: https://leetcode.com/problems/continuous-subarray-sum/#/description
// Given an array of non-negative numbers and a target integer k, determine if the array has a 
// subarray (>= 2 elements) whose sum is a multiple of k.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

// Accepted. 26ms. Beats 78.76% of submissions.
class Solution {
public:
    bool checkSubarraySum(const std::vector<int>& nums, int k) {
        if (nums.size() <= 1) { return false; }
        int sum = 0;
        std::unordered_map<int, int> remainders(nums.size() * 2);

        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (k == 0) {
                if (sum == 0 && i > 0) return true;
            } else {
                int remainder = sum % k;
                auto found = remainders.find(remainder);
                if ((i > 0 && remainder == 0) || 
                    (found != remainders.end() && found->second < i-1))  { return true; }
                remainders.emplace(remainder,i);
            }

        }
        return false;
    }
};

void test_check_subarray_sum() {
    Solution soln;
    assert(soln.checkSubarraySum({0,0}, 0) == true);
    assert(soln.checkSubarraySum({0,2,0}, 2) == true);
    assert(soln.checkSubarraySum({1,2,3,4,0,1}, 1) == true);
    assert(soln.checkSubarraySum({1,2,3,4,0,1}, 2) == true);
    assert(soln.checkSubarraySum({1,2,3,4,0,1}, 4) == true);
    assert(soln.checkSubarraySum({1,2,3,4,0,1}, 6) == true);
    assert(soln.checkSubarraySum({1,2,2,4,0,2}, 7) == false);
    assert(soln.checkSubarraySum({1,2,3,4,0,1}, 12) == false);
    assert(soln.checkSubarraySum({2,2,2,2,2,2}, 7) == false);
    assert(soln.checkSubarraySum({0,0,0,2,2,2}, 2) == true);
    assert(soln.checkSubarraySum({0,0,0,2,2,2}, 4) == true);
    assert(soln.checkSubarraySum({0,0,0,2,0,2}, 4) == true);
}

int main(int argc, char** argv) {
    test_check_subarray_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
