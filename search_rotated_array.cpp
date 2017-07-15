// Leetcode: https://leetcode.com/problems/search-in-rotated-sorted-array/#/description
// Given a sorted array that has been rotated some number of times, search for a target value.
// (e.g., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2), search for 4. Return the index of the item
// if it is found, -1 if not. The array does not contain duplicate items.

// Brute Force: Perform a linear scan. O(n) time.
// Better: Modified binary search. Divide the array into halves. For each half, if the half is 
// sorted and the target is in the sorted range, recurse on that half. If the half is unsorted, 
// and the target is either >= the first item or <= last item then also recurse.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 43.98% of submissions, ties 50.96% of submisssions
class Solution {
public:

    int modified_bsearch(const std::vector<int>& nums, int left, int right, int target) {
        if (left > right) { return -1; }
    
        int middle = left + (right - left) / 2;
        if (nums[middle] == target) {
            return middle;
        } else if (nums[middle] < nums[right] && (target > nums[middle] && target <= nums[right])) {
            return modified_bsearch(nums, middle+1, right, target);
        } else if (nums[middle] > nums[right] &&  (target > nums[middle] || target <= nums[right])){
            return modified_bsearch(nums, middle+1, right, target);
        } else if (nums[left] < nums[right] && (target >= nums[left] && target < nums[middle])) {
            return modified_bsearch(nums, left, middle-1, target);
        } else if (nums[left] > nums[right] && (target >= nums[left] || target < nums[middle])) {
            return modified_bsearch(nums, left, middle-1, target);
        }
        return -1;
    }

    int search(const std::vector<int>& nums, int target) {
        return modified_bsearch(nums, 0, nums.size() - 1, target);
    }
};

void test_rotated_search() {
    Solution soln;

    assert(soln.search({}, 6) == -1);
    assert(soln.search({5}, 5) == 0);
    assert(soln.search({5}, 6) == -1);
    assert(soln.search({4,5,6,7,0,1,2}, 6) == 2);
    assert(soln.search({4,5,6,7,0,1,2}, 4) == 0);
    assert(soln.search({4,5,6,7,0,1,2}, 2) == 6);
    assert(soln.search({4,5,6,7,0,1,2}, 7) == 3);
    assert(soln.search({10,11,0,1,2,3,5}, 7) == -1);
    assert(soln.search({10,11,0,1,2,3,5}, 10) == 0);
    assert(soln.search({10,11,0,1,2,3,5}, 11) == 1);
    assert(soln.search({10,11,0,1,2,3,5}, 0) == 2);
    assert(soln.search({10,11,0,1,2,3,5}, 1) == 3);
    assert(soln.search({10,11,0,1,2,3,5}, 2) == 4);
    assert(soln.search({10,11,0,1,2,3,5}, 3) == 5);
    assert(soln.search({10,11,0,1,2,3,5}, 5) == 6);
    assert(soln.search({10,11,0,1,2,3,5}, 15) == -1);
    assert(soln.search({5,6,7,8,9,0,1,2}, 15) == -1);
    assert(soln.search({5,6,7,8,9,0,1,2}, 2) == 7);
    assert(soln.search({5,6,7,8,9,0,1,2}, 1) == 6);
}

int main(int argc, char** argv) {
    test_rotated_search();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
