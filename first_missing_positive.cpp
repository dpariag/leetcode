// Leetcode: https://leetcode.com/problems/first-missing-positive/
// Given an unsorted integer array, find the first missing positive integer.
// Example: Given [1,2,0] return 3. Given [3,4,-1,1] return 2.

#include <vector>
#include <iostream>
#include <assert.h>

// Brute Force: Try each number from 1..n, testing if it is in the array. 
// O(n^2) time if scanning an unsorted array. Sort the array and use binary search => O(n*logn). 
// Can use an auxiliary hash map to get O(n) runtime with O(n) additional space
//
// Better: Treat the array as a permutation of the numbers 1..n. 
// Iterate the array, putting each <number> at index <number-1>. 
// For example, 1 moves to index 0 (if not already there), 2 moves to index 1, etc.
// O(n) time and O(1) additional space

using Numbers = std::vector<int>;

// Accepted. Runtime 3ms. Beats 20.4% of submissions, ties 74.55% of submissions.
class Solution {
public:
    int firstMissingPositive(Numbers& nums) {

        int i = 0;
        while (i < nums.size()) {
            if (nums[i] > 0 && nums[i] <= nums.size()) {
                auto dest = nums[i] - 1;
                if (nums[dest] != nums[i]) {
                    std::swap(nums[i], nums[dest]);
                    continue;
                }
            }
            ++i;
        }

        i = 0;
        while (i < nums.size()) {
            if (nums[i] != i + 1) { return i + 1; }
            ++i;
        }
        return nums.size() + 1;
    }
};

bool test_first_missing_positive(const Numbers& nums, int expected) {
    Solution soln;
    Numbers copy(nums);

    int first_missing = soln.firstMissingPositive(copy);
    return (first_missing == expected);
}

void test_first_missing() {
    assert(test_first_missing_positive({1,2,0}, 3));
    assert(test_first_missing_positive({3,4,-1,1}, 2));
    assert(test_first_missing_positive({6,2,5,1,4}, 3));
    assert(test_first_missing_positive({1,1,1,1,1}, 2));
    assert(test_first_missing_positive({1,1,2,1,1}, 3));
    assert(test_first_missing_positive({0,1,2,1,-1}, 3));
    assert(test_first_missing_positive({0,0,-1}, 1));
    assert(test_first_missing_positive({1,2,3,4,5,6}, 7));
    assert(test_first_missing_positive({6,5,4,3,2,1}, 7));
    assert(test_first_missing_positive({6,6,4,3,2,1}, 5));
    assert(test_first_missing_positive({6,5,5,3,2,1}, 4));
}

int main(int argc, char** argv) {
    test_first_missing();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
