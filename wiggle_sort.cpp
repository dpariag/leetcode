// Leetcode: https://leetcode.com/problems/wiggle-sort/description/
// Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

// Brute Force: Sort the array, then choose pairs nums[0],nums[n-1],nums[1],nums[n-2],... O(n*logn) time.
// Better: Conceptually, two passes. First pass performs swaps to order nums[1] >= nums[2], nums[3] >= nums[4] etc.
// Second pass performs swaps to order nums[0] <= nums[1], nums[1] <= nums[2], etc.
// Swaps in the second pass cannot violate the ordering achieved in the first pass.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 39ms. Beats 52.41% of submissions, ties 31.30% of submissions.
class Solution {
public:
    void wiggleSort(std::vector<int>& nums) {
        int i = 1;
        while (i < int(nums.size())) {
            if (i+1 < int(nums.size()) && nums[i] < nums[i+1]) { std::swap(nums[i], nums[i+1]); }
            if (nums[i-1] > nums[i]) { std::swap(nums[i-1], nums[i]); }
            i+= 2;
        }
    }
};

bool test_wiggle_sort(std::vector<int> nums) {
    Solution soln;    

    soln.wiggleSort(nums);
    const int sz = nums.size();
    for (int i = 0; i < sz; ++i) {
        if (i % 2 == 0 && i+1 < sz && nums[i] > nums[i+1]) { return false; }
        if (i % 2 == 1 && i+1 < sz && nums[i] < nums[i+1]) { return false; }
    }
    return true;
}

void test_wiggle_sort() {
    assert(test_wiggle_sort({}));
    assert(test_wiggle_sort({1}));
    assert(test_wiggle_sort({1,2}));
    assert(test_wiggle_sort({2,1}));
    assert(test_wiggle_sort({2,1,3}));
    assert(test_wiggle_sort({3,3,3}));
    assert(test_wiggle_sort({3,3,3,3}));
    assert(test_wiggle_sort({8,9,9,4,4,5,4,8,15}));
    assert(test_wiggle_sort({1,1,2,2,4,6,7,8}));
}

int main(int argc, char** argv) {
    test_wiggle_sort();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}