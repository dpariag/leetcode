// Leetcode: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
// Given a sorted array of integers, enforce a cardinality of at most 2 for each item.
// Example: Given {1,1,1,2,2,3} the resulting array is {1,1,2,2,3}

// Brute Force: Use extra storage (e.g, hash_map + extra array) to track cardinality of each element.
// Better: Can be done in place using a read and write index, and implementing carefully.

#include <vector>
#include <iostream>
#include <assert.h>
#include "numbers.h"

// Accepted. 13ms. Beats 42.77% of solutions and ties 46.49% of solutions.
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() <= 2) { return nums.size(); }
        int write = 0, read = 1, item_count = 1;

        while (read < nums.size()) {
            if (nums[write] == nums[read]) {
                ++write;
                nums[write] = nums[read];
                if (item_count == 0) {
                    item_count = 1;
                    ++read;
                } else {
                    // item_count == 1
                    while (read < nums.size() && nums[read] == nums[write]) {++read;}
                    item_count = 0;
                }
            } else {
                ++write;
                nums[write] = nums[read];
                item_count = 1;
                ++read;
            }
        }
        return write + 1;
    }
};

bool test_remove_duplicates(std::vector<int> nums, std::vector<int> expected) {
    Solution soln;
    auto num_unique = soln.removeDuplicates(nums);

    for (auto i = 0; i < expected.size(); ++i) {
        if (expected[i] != nums[i]) { return false; }
    }
    return num_unique == expected.size(); 
}

void test_remove_duplicates() {
    assert(test_remove_duplicates({}, {}));
    assert(test_remove_duplicates({1}, {1}));
    assert(test_remove_duplicates({1,2}, {1,2}));
    assert(test_remove_duplicates({2,2,2,2,2}, {2,2}));
    assert(test_remove_duplicates({2,2,2,2,2,3}, {2,2,3}));
    assert(test_remove_duplicates({1,2,14,15}, {1,2,14,15}));
    assert(test_remove_duplicates({1,1,2}, {1,1,2}));
    assert(test_remove_duplicates({1,2,2,2,2,3,4,5,5,6}, {1,2,2,3,4,5,5,6}));
    assert(test_remove_duplicates({1,1,2,2,2,2,3,4,5,5,6}, {1,1,2,2,3,4,5,5,6}));
    assert(test_remove_duplicates({1,1,1,2,2,2,2,3,4,5,5,6}, {1,1,2,2,3,4,5,5,6}));
    assert(test_remove_duplicates({1,1,1,2,2,2,2,3,4,5,5,6,6,6,6}, {1,1,2,2,3,4,5,5,6,6}));
}

int main(int argc, char** argv) {
    test_remove_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
