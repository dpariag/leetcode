// Leetcode: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
// Find the min element in a sorted array of unique integers, that has been rotated an unknown 
// number of times.

// Brute Force: Scan the array to find the min. O(n) time.
// Better: Modified binary search. O(logN) time.

#include <vector>
#include <iostream>
#include <limits>
#include <assert.h>

// Accepted. 3ms. Beats 24.72% of submissions, ties 75.28% of submissions.
class Solution {
public:
    int find_min(const std::vector<int>& nums, int start, int end) {
        int min = std::numeric_limits<int>::max(); 
        
        while (start < end) {
            int mid = start + (end - start) / 2;
            min = std::min(min, nums[mid]);

            if (nums[mid] < nums[end]) {
                // Recurse on LHS
                end = mid - 1;
            } else {
                // Recurse on RHS
                start = mid + 1;
            }
        }
        return std::min(min, nums[start]);
    }

    int findMin(const std::vector<int>& nums) {
        return find_min(nums, 0, nums.size() - 1);
        return 0;
    }
};

void test_find_min() {
    Solution soln;

    assert(soln.findMin({3}) == 3);
    assert(soln.findMin({3,4}) == 3);
    assert(soln.findMin({4,3}) == 3);
    assert(soln.findMin({1,2,3,4,5}) == 1);
    assert(soln.findMin({4,5,1,2,3}) == 1);
    assert(soln.findMin({4,5,6,1,2,3}) == 1);
    assert(soln.findMin({4,5,6,2,3}) == 2);
    assert(soln.findMin({-1,2,3,4,5,6}) == -1);
    assert(soln.findMin({6,-1,2,3,4,5}) == -1);
    assert(soln.findMin({5,6,-1,2,3,4}) == -1);
    assert(soln.findMin({4,5,6,-1,2,3}) == -1);
    assert(soln.findMin({3,4,5,6,-1,2}) == -1);
    assert(soln.findMin({2,3,4,5,6,-1}) == -1);
}

int main(int argc, char** argv) {
    test_find_min();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
