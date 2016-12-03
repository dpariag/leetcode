// Leetcode: https://leetcode.com/problems/single-number-ii/
// Given an array of integers, every element appears 3 times except for one. Find that single one.

// Brute Force: Use a hash_map to count each element. O(n) time and space.
// Better: Can reduce O(n) space requirement of brute force solution by counting the occurrences
// of each bit in the array elements. Each bit should occur a multiple of 3 times, except for the
// bits which make up the singly occuring element. Leads to an O(n) time and O(1) space solution.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 26ms. Beats 10.89% of solutions, ties 26.00% of solutions.
class Solution {
public:
    inline int singleNumber(std::vector<int>& nums) {
        int bit = 1, single = 0;

        auto max = *std::max_element(nums.begin(), nums.end());
        auto min = *std::min_element(nums.begin(), nums.end());
        while (bit != 0 && (bit <= max || min < 0)) {
            int bit_count = 0;
            for (auto n : nums) {
                if ((n & bit) != 0) { ++bit_count; }
            }
            if (bit_count % 3 == 1) { single |= bit; }
            bit <<= 1;
        }
        return single;
    }
};

bool test_single_number(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.singleNumber(nums) == expected;
}

void test_single_number() {
    assert(test_single_number({-2,-2,1,1,-3,1,-3,-3,-4,-2}, -4));
    assert(test_single_number({1}, 1));
    assert(test_single_number({1,1,1,184}, 184));
    assert(test_single_number({1,1,1,18,18,19,18}, 19));
    assert(test_single_number({1,2,1,18,18,19,18,1,19,19}, 2));
}

int main(int argc, char** argv) {
    test_single_number();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
