// Leetcode: https://leetcode.com/problems/reverse-pairs/description/
// Given an array nums, (i,j) is a reverse pair if i < j and nums[i] > 2*nums[j].
// You need to return the number of reverse pairs in nums.

// Brute Force: For each i, scan to the end of the array counting reversed pairs. O(n^2)
// Better: Use a mergesort based approach. During merge, first count inverted pairs, then merge.
// O(n*logn) time and O(n) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 190ms. Beats 79.94% of submissions, ties < 1% of submissions.
class Solution {
public:

    void merge_pairs(std::vector<int>& nums, std::vector<int>& space, 
                     int start, int end, int& count) {
        if (start >= end) { return; }
        
        int mid = start + (end-start) / 2;
        merge_pairs(nums, space, start, mid, count);
        merge_pairs(nums, space, mid+1, end, count);

        // Count inverted pairs
        int left = start, right = mid+1;
        while (left <= mid && right <= end) {
            while (right <= end && int64_t(nums[left]) > int64_t(nums[right]) * int64_t(2)) {
                count += (mid - left) + 1;
                ++right;
            }
            ++left;
        }

        // Merge the two sorted halves
        for (int i = start; i <= end; ++i) { space[i] = nums[i]; }
        left = start, right = mid+1;
        int dest = start;
        while (left <= mid && right <= end) {
            if (space[left] <= space[right]) {
                nums[dest++] = space[left++];
            } else {
                nums[dest++] = space[right++];
            }
        }
        while (left <= mid) { nums[dest++] = space[left++]; }
        while (right <= end) { nums[dest++] = space[right++]; }
    }

    int reversePairs(std::vector<int>& nums) {
        int count = 0;
        std::vector<int> space(nums.size(), 0);

        merge_pairs(nums, space, 0, nums.size() - 1, count);
        return count;
    }
};

bool test_reverse_pairs(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.reversePairs(nums) == expected;
}

void test_reverse_pairs() {
    assert(test_reverse_pairs({13}, 0));
    assert(test_reverse_pairs({13,10}, 0));
    assert(test_reverse_pairs({13,5}, 1));
    assert(test_reverse_pairs({1,3,2,3,1}, 2));
    assert(test_reverse_pairs({2,4,8,1,2}, 3));
    assert(test_reverse_pairs({2,4,3,5,1}, 3));
    assert(test_reverse_pairs({2147483647,2147483647,-2147483647,-2147483647,-2147483647,2147483647}, 9));
    assert(test_reverse_pairs({233,2000000001,234,2000000006,235,2000000003,236,2000000007,
                               237,2000000002,2000000005,233,233,233,233,233,2000000004}, 40));
}

int main(int argc, char** argv) {
    test_reverse_pairs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
