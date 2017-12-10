// Leetcode: https://leetcode.com/problems/single-element-in-a-sorted-array/description/
// Given a sorted array consisting of only integers where every element appears twice except 
// for one element which appears once. Find this single element that appears only once.

// Brute Force: Scan the array counting pairs of consecutive elements. O(n) time.
// Better: Use modified binary search. Since elements occur in pairs, note the index of the last element
// in the middle pair. If there middle pair ends on an odd index, recurse on the right half.
// If it ends on an even index, recurse on the left half. If there is no middle pair, found the singleton.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 15.63% of submissions, ties 80% of submissions.
class Solution {
public:
    int find_single_elem(const std::vector<int>& nums, int start, int end) {
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (mid > start && nums[mid-1] == nums[mid]) {
                if (mid % 2 == 0) {
                    end = mid - 2;
                } else {
                    start = mid + 1;
                }
            } else if (mid < end && nums[mid] == nums[mid+1]) {
                if ((mid+1) % 2 == 0) {
                    end = mid - 1;
                } else {
                    start = mid + 2;
                }
            } else {
                return nums[mid];
            }
        }
        return nums[start];
    }

    int singleNonDuplicate(const std::vector<int>& nums) {
        return find_single_elem(nums, 0, nums.size() - 1);
    }
};

void test_single_elem() {
    Solution soln;

    assert(soln.singleNonDuplicate({3}) == 3);
    assert(soln.singleNonDuplicate({2,2,3}) == 3);
    assert(soln.singleNonDuplicate({2,3,3}) == 2);
    assert(soln.singleNonDuplicate({1,2,2,3,3}) == 1);
    assert(soln.singleNonDuplicate({2,2,3,4,4}) == 3);
    assert(soln.singleNonDuplicate({2,2,3,3,4}) == 4);
    assert(soln.singleNonDuplicate({2,2,4,4,5}) == 5);
    assert(soln.singleNonDuplicate({2,4,4,5,5}) == 2);
    assert(soln.singleNonDuplicate({2,2,3,3,4,5,5}) == 4);
    assert(soln.singleNonDuplicate({2,2,3,3,4,4,5}) == 5);
    assert(soln.singleNonDuplicate({2,3,3,4,4,5,5}) == 2);
    assert(soln.singleNonDuplicate({2,2,3,4,4,5,5}) == 3);
    assert(soln.singleNonDuplicate({2,2,3,3,4,5,5}) == 4);
    assert(soln.singleNonDuplicate({2,2,3,3,4,4,5}) == 5);

}

int main(int argc, char** argv) {
    test_single_elem();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
