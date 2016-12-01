// Leetcode: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// Given a sorted array, remove any duplicates in place. Return the resulting array length.

// Brute Force: Use extra space (e.g., a hash table, or separate array) to count. O(n) time & space.
// Better: O(n) time and O(1) space is posible with a careful implementation that maintains
// two indices (read, write) and overwrites duplicate entries.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 26ms. Runtime beats 53.07% of submissions and ties 34.13% of submissions.
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.size() <= 1) { return nums.size(); }
        int write = 0, read = 1;

        while (read < nums.size()) {
            if (nums[write] != nums[read]) {
                ++write;
                nums[write] = nums[read];
            }
            ++read;
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
    assert(test_remove_duplicates({2,2,2,2,2}, {2}));
    assert(test_remove_duplicates({1,2,14,15}, {1,2,14,15}));
    assert(test_remove_duplicates({1,1,2}, {1,2}));
    assert(test_remove_duplicates({1,1,2,2,2,2,3,4,5,5,6}, {1,2,3,4,5,6}));
}

int main(int argc, char** argv) {
    test_remove_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
