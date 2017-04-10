// Leetcode: https://leetcode.com/problems/first-missing-positive/#/description
// Given an unsorted integer array, find the first missing positive integer.
// Example: [1,2,0] ==> return 3, and [3,4,-1,1] ==> return 2.

// Brute Force: Sort the array and iterate looking for a gap. O(n*logn) time.
// Better: Use a hash map to store positive elements <= size. O(n) time and space.
// Can be done in O(1) space if we use the array itself for storage and lookup.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 16.14% of submissions and ties 54.52% of submissions.
class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        // First pass: store i in nums[i-1]
        auto i = 0u;
        while (i < nums.size()) {
            if (nums[i] <= 0 || nums[i] >= nums.size() + 1) {
                ++i;
            } else {
                if (nums[i] == nums[nums[i]-1]) {
                    ++i;
                    continue;
                }
                std::swap(nums[i], nums[nums[i]-1]);
                if (nums[i] == i+1) ++i;
            }
        }

        // Second pass: Look for the first element where nums[i] != i+1
        i = 0u;
        while (i < nums.size()) {
            if (nums[i] != i+1) {
                return i+1;
            }
            ++i;
        }
        return nums.size() + 1;            
    }
};

bool test_first_missing(std::vector<int> nums, int missing) {
    Solution soln;
    return (soln.firstMissingPositive(nums) == missing);
}

void test_first_missing() {
    assert(test_first_missing({}, 1));
    assert(test_first_missing({0}, 1));
    assert(test_first_missing({110}, 1));
    assert(test_first_missing({1,1}, 2));
    assert(test_first_missing({1,2,3}, 4));
    assert(test_first_missing({0,1,2,3}, 4));
    assert(test_first_missing({0,1,3}, 2));
    assert(test_first_missing({0,1,2}, 3));
    assert(test_first_missing({0,3,2}, 1));
    assert(test_first_missing({0,3,12}, 1));
    assert(test_first_missing({0,1,12}, 2));
}

int main(int argc, char** argv) {
    test_first_missing();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
