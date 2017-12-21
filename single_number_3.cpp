// Leetcode: https://leetcode.com/problems/single-number-iii/description/ 
// Given an array of numbers nums, in which exactly two elements appear only once and all the other 
// elements appear exactly twice. Find the two elements that appear only once.

// Approach: Use three passes of the array using XOR properties

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 12ms. Beats 85.57% of submissions, ties 10.91% of submissions.
class Solution {
public:
    std::vector<int> singleNumber(const std::vector<int>& nums) {
        std::vector<int> result;
        int mask = 0;
        
        // XOR all elements together, the resulting mask is bits exclusive to
        // the singularly occurring elements.
        for (auto n : nums) { mask = mask ^ n; }

        // Extract the rightmost bit of the mask
        int bit = mask & ~(mask-1);

        // Calculate the XOR of elems with that rightmost bit set
        // This is one of the elements
        int value = 0;
        for (auto n : nums) {
            if (n & bit) { value = value ^ n; }
        }
        result.emplace_back(value);
        
        // Calculate the array XOR again, including the element found above.
        // This yields the second element.
        for (auto n : nums) { value = value ^ n; }
        result.emplace_back(value);
        return result;
    }
};

bool test_single_number(std::vector<int> nums, std::vector<int> expected) {
    Solution soln;
    
    auto result = soln.singleNumber(nums);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return result == expected;
}

void test_single_number() {
    assert(test_single_number({2,34}, {34,2}));
    assert(test_single_number({1,1,2,34}, {34,2}));
    assert(test_single_number({1,2,1,2,3,4}, {3,4}));
    assert(test_single_number({1,2,1,2,3,3,18,54}, {18,54}));
}

int main(int argc, char** argv) {
    test_single_number();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
