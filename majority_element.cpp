// Leetcode: https://leetcode.com/problems/majority-element/
// Given an array of size n, find the majority element. The majority element is the element that 
// appears more than floor(n/2) times. Assume a majority element always exists.

// Brute Force: Count the elements using a hash table, then iterate the table to find a majority.
// O(n) time and space.
// Better: Boyer-Moore Majority vote algorithm. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 19ms. Beats 92.84% of submissions and ties 5.60% of submissions.
class Solution {
public:
    int majorityElement(const std::vector<int>& nums) {
        int candidate = nums[0];
        int count = 1;

        for (auto i = 0; i < nums.size(); ++i) {
            count += (nums[i] == candidate) ? 1 : -1;
            if (count == 0) {
                candidate = nums[i];
                count = 1;
            }
        }
        return candidate;
    }
};

bool test_majority_element(const std::vector<int>& nums, int expected) {
    Solution soln;
    return soln.majorityElement(nums) == expected;
}

void test_majority_element() {
    assert(test_majority_element({1}, 1));
    assert(test_majority_element({1,1,1}, 1));
    assert(test_majority_element({1,2,1,1,2}, 1));
    assert(test_majority_element({1,2,1,1,2,5,5,5,5,5,5}, 5));
    assert(test_majority_element({5,2,5,1,2,5,1,1,5,5,5}, 5));
    assert(test_majority_element({5,2,5,2,5,2,5,2,5,2,5}, 5));
}

int main(int argc, char** argv) {
    test_majority_element();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
