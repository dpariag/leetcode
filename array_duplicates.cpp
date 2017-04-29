// Leetcode: https://leetcode.com/problems/find-all-duplicates-in-an-array/#/description
// Given an array of n integers, where 1 ≤ A[i] ≤ n, and each element appears exactly once or twice,
// find all the elements that appear twice.

// Brute Force: Use a hash map to count how many time each element appears
// Better: Take advantage of the fact that 1 <= A[i] <= n, by storing A[i] at index i-1

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 126ms. Beats 95.21% of submissions, ties 3.03% of submissions.
class Solution {
public:
    std::vector<int> findDuplicates(std::vector<int>& nums) {
        std::vector<int> appears_twice;
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] == i+1) {
                // Already in the right spot
                ++i;
            } else {
                if (nums[i] == nums[nums[i]-1]) {
                    // Duplicate
                    appears_twice.emplace_back(nums[i]);
                    ++i;
                } else {
                    // Swap
                    auto dest = nums[i]-1;
                    std::swap(nums[i], nums[nums[i]-1]);
                    // Check for swap with earlier, already processed element
                    if (dest < i) { ++i; }
                }
            }
        }
        return appears_twice;
    }
};

bool test_find_duplicates(std::vector<int> nums, std::vector<int> expected_duplicates) {
    Solution soln;
    auto duplicates = soln.findDuplicates(nums);
    std::sort(duplicates.begin(), duplicates.end());
    std::sort(expected_duplicates.begin(), expected_duplicates.end());
    return duplicates == expected_duplicates;
}

void test_find_duplicates() {
    assert(test_find_duplicates({},{}));
    assert(test_find_duplicates({1},{}));
    assert(test_find_duplicates({1,1},{1}));
    assert(test_find_duplicates({3,1,1},{1}));
    assert(test_find_duplicates({1,2,3,4,5},{}));
    assert(test_find_duplicates({1,1,3,4,5},{1}));
    assert(test_find_duplicates({1,1,3,3,5},{1,3}));
    assert(test_find_duplicates({1,1,3,3,5,5},{1,3,5}));
    assert(test_find_duplicates({5,5,3,3,1,1},{1,3,5}));
    assert(test_find_duplicates({4,3,2,7,8,2,3,1},{2,3}));
    assert(test_find_duplicates({10,2,5,10,9,1,1,4,3,7}, {10,1}));
    assert(test_find_duplicates({3,11,8,16,4,15,4,17,14,14,6,6,2,8,3,12,15,20,20,5},
                                {3,4,6,8,14,15,20}));
}

int main(int argc, char** argv) {
    test_find_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
