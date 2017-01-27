// Leetcode: https://leetcode.com/problems/majority-element-ii/
// Given an integer array of size n, find all elements that appear more than ⌊n/3⌋ times. 
// The algorithm should run in linear time and in O(1) space.

// Brute Force: Use a hash table to count elements. O(n) time and space.
// Better: Generalize the Boyer-Moore majority vote algorithm to use three counters.

#include <vector>
#include <iostream>
#include <assert.h>

using Elements = std::vector<int>;

// Accepted. 16ms. Beats 54.90% of submissions, ties 38.11% of submissions.
class Solution {
public:
    Elements find_majority_elements(const Elements& nums, int c1, int c2, int c3 ) {
        Elements elements;
        int c1_count = 0, c2_count = 0, c3_count = 0;

        for (auto n : nums) {
            if (n == c1) { ++c1_count; }
            else if (n == c2) { ++c2_count; }
            else if (n == c3) { ++c3_count; } 
        }

        int threshold = nums.size() / 3;
        if (c1_count > threshold) { elements.emplace_back(c1); }
        if (c2_count > threshold) { elements.emplace_back(c2); }
        if (c3_count > threshold) { elements.emplace_back(c3); }
        return elements;
    }

    Elements majorityElement(const Elements& nums) {
        int candidate1, candidate2, candidate3;
        int count1 = 0, count2 = 0, count3 = 0;
        int i = 0;
        while (i < nums.size()) {
            if (count1 > 0 && candidate1 == nums[i]) {
                ++count1;
            } else if (count2 > 0 && candidate2 == nums[i]) {
                ++count2;
            } else if (count3 > 0 && candidate3 == nums[i]) {
                ++count3;
            } else if (count1 == 0) {
                candidate1 = nums[i];
                ++count1;
            } else if (count2 == 0) {
                candidate2 = nums[i];
                ++count2;
            } else if (count3 == 0) {
                candidate3 = nums[i];
                ++count3;
            } else {
                --count1;
                --count2;
                --count3;
                continue;
            }
            ++i;
        } // while
        return find_majority_elements(nums, candidate1, candidate2, candidate3);
    }
};

void test_majority_element_2() {
    Solution soln;
    assert(soln.majorityElement({}) == Elements({}));
    assert(soln.majorityElement({1}) == Elements({1}));
    assert(soln.majorityElement({1,1,1,1}) == Elements({1}));
    assert(soln.majorityElement({1,2,2,1,2,2,4,5}) == Elements({2}));
    assert(soln.majorityElement({1,1,2,2,1,2,2,4,5,1}) == Elements({1,2}));
    assert(soln.majorityElement({1,1,2,2,1,2,2,4,5,1,1,1,1}) == Elements({1}));
    assert(soln.majorityElement({1,5,2,5,1,2,5,4,5,1,5,5,1}) == Elements({5}));
}

int main(int argc, char** argv) {
    test_majority_element_2();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
