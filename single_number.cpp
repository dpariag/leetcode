// Leetcode: https://leetcode.com/problems/single-number/ 
// Given an integer array where every element appears twice except for one, which appears once.
// Find the element which appears once.

// Brute Force: Count elements using a hash map. O(n) time and space.
// Better: Compute the XOR or all elements in the array. Since x^x == 0, elements occuring twice
// will not contribute to the XOR, leaving only the element which occurs once.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 16ms. Beats 47.81% of submissions, ties 49.05% of submissions.
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int xor_all = 0;
        for (auto n : nums) { xor_all = xor_all ^ n; }
        return xor_all;
    }
};

bool test_single_number(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.singleNumber(nums) == expected;
}

void test_single_number() {
    assert(test_single_number({3,4,4}, 3));
    assert(test_single_number({2,2,3,4,4}, 3));
    assert(test_single_number({2,2,3,3,4,4,11}, 11));
}

int main(int argc, char** argv) {
    test_single_number();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
