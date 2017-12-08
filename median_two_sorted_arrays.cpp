// Leetcode: https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// Given two sorted arrays, find their median in logarithmic time.

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 49ms. Beats 77.49% of submissions, ties 5.94 of submissions.
class Solution {
public:
    // nums is a sorted array. Return:
    // 0 if value could be inserted at index without violating the sortedness property.
    // 1 if value would lie to the right of index
    // -1 if value would lie to the left of the index
    inline int check_position(const Numbers& nums, int index, int value) {
        //std::cout << "Checking " << value << " against index " << index << std::endl;
        if (index == -1 && value <= nums.front()) { return 0; }
        if (index == nums.size() && value >= nums.back()) { return 0; }
        if (index < 0) { return 1; }
        if (index >= nums.size()) { return -1; }
        
        if (value <= nums[index]) {
            if (index == 0) return 0;
            return (value >= nums[index-1] ? 0 : -1);
        }
        return 1;
    }

    inline int get_next(const Numbers& nums, int index) {
        if (index < nums.size()-1) {
            return nums[index+1];
        }
        return std::numeric_limits<int>::max();
    }

    inline double array_median(const Numbers& nums) {
        int size = nums.size();
        if (size % 2) {
            return double(nums[size/2]);
        }
        return double(nums[size/2] + nums[(size/2)-1]) / 2.0;
    }

    // Binary search nums1 for the median of both arrays
    bool find_median(const Numbers& nums1, const Numbers& nums2, double& result) {
        int total_size = nums1.size() + nums2.size();
        int median_index = total_size / 2;
        median_index -= (total_size % 2) == 0 ? 1 : 0;
        int left = 0, right = nums1.size() - 1;

        while (left <= right) {
            int mid = left + (right-left) / 2;
            int nums2_index = median_index - mid;

            int check = check_position(nums2, nums2_index, nums1[mid]);

            if (mid > median_index || check == 1) {
                right = mid - 1;                
            } else if (check == -1) {
                left = mid + 1;
            } else if (check == 0) {
                if (total_size % 2) {
                    result = nums1[mid];
                } else {
                    int next_in_nums2 = nums2_index < nums2.size() ? nums2[nums2_index] : std::numeric_limits<int>::max();
                    result = double(nums1[mid] + std::min(get_next(nums1, mid), next_in_nums2)) / 2;
                }             
                return true;
            }
        }        
        return false;
    }

    double findMedianSortedArrays(const Numbers& nums1, const Numbers& nums2) {
        if (nums1.empty()) { return array_median(nums2); }
        if (nums2.empty()) { return array_median(nums1); }

        double result = 0.0;
        find_median(nums1, nums2, result) || find_median(nums2, nums1, result);
        return result;
    }
};

bool test_find_median(Numbers nums1, Numbers nums2) {
    Solution soln;

    auto median = soln.findMedianSortedArrays(nums1, nums2);
    auto merged = nums1;
    merged.insert(merged.end(), nums2.begin(), nums2.end());
    std::sort(merged.begin(), merged.end());
    auto mid = merged.size() / 2;
    auto expected_median = (merged.size() % 2) ? double(merged[mid]) : double((merged[mid-1] + merged[mid])) / 2.0;
    return expected_median == median;
}

void test_find_median() {
    assert(test_find_median({6},{1,2,3,4,5,7}));
    assert(test_find_median({1},{2,3,4}));
    assert(test_find_median({1,2,3,4,5},{95,96,97,98,99,100,103,104,105}));
    assert(test_find_median({1},{4}));
    assert(test_find_median({1,2},{4}));
    assert(test_find_median({1,2,3},{4}));
    assert(test_find_median({1,2,3,4},{}));
    assert(test_find_median({}, {1,2,3,4}));
    assert(test_find_median({}, {1,2,3,4,5}));
    assert(test_find_median({1,2,3,4,5},{}));    
    assert(test_find_median({1,2,3,4,5},{103,104,105}));
    assert(test_find_median({1,2,3,4},{103,104,105}));
    assert(test_find_median({1,2,3,4},{3,4,5}));
    assert(test_find_median({1,2,3},{3,4,5}));
    assert(test_find_median({1,2},{3,4,5}));
    assert(test_find_median({1,2,3},{4,5,6}));
    assert(test_find_median({1,2},{3}));
    assert(test_find_median({1,2},{3,4}));    
}

int main(int argc, char** argv) {
    test_find_median();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
