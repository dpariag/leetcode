// Leetcode: https://leetcode.com/problems/maximum-subarray/
// Find the non-empty, contiguous, subarray which has the largest sum.
// Example: Given the array [-2,1,-3,4,-1,2,1,-5,4], the subarray [4,-1,2,1] has the largest sum (6).

#include <vector>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

class Solution {
public:
    int maxSubArray(Numbers& nums) {
        return 0;
    }
};

bool test_max_subarray(const Numbers& nums, int expected_max) {
    Solution soln;
    Numbers copy(nums);
    return soln.maxSubArray(copy) == expected_max;
}

void test_max_subarray() {
    assert(test_max_subarray({-2,1,-3,4,-1,2,1,-5,4}, 6));
}

int main(int argc, char** argv) {
    test_max_subarray();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
