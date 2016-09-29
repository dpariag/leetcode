// Leetcode: https://leetcode.com/problems/search-for-a-range/ 
// Given a sorted array of integers, find the starting and ending indices of a given value.
// Return [-1, -1] if the target is not found.
// Example: Given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].

// Brute Force: Linear scan of the array looking for target. O(n) time.
// Better: Perform 3 binary searches. The first search locates the target in the array.
// The second and third searches extend the range to the right and left if duplicates of 
// target exist in the array.

#include <vector>
#include <iostream>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 9ms runtime. Beats 43.56% of submissions, ties 56.37% of submissions.
class Solution {
public:
    Numbers searchRange(Numbers& nums, int target) {
        Numbers result({-1,-1});
        int start = 0; int end = nums.size() - 1, mid = start;
       
        // Binary search for the target 
        while (start <= end) {
            mid = start + (end - start) / 2;
            if (nums[mid] == target) {
                result.front() = mid;
                result.back() = mid;
                break;
            } else if (nums[mid] < target) {
                start = mid + 1;
            } else { // nums[mid] > target
                end = mid - 1;
            }
        }

        // Binary search to the right of mid, looking for duplicates
        start = mid + 1;
        end = nums.size() - 1;
        while (start <= end) {
            int rhs_end = start + (end - start) / 2;
            if (nums[rhs_end] == target) {
                result.back() = std::max(result.back(), rhs_end);
                start = rhs_end + 1;
            } else if (nums[rhs_end] > target) {
                end = rhs_end - 1;
            }
        }

        // Binary search to the left of mid, looking for duplicates 
        start = 0; 
        end = mid - 1;
        while (start <= end) {
            int lhs_end = start + (end - start) / 2; 
            if (nums[lhs_end] == target) {
                result.front() = std::min(result.front(), lhs_end);
                end = lhs_end - 1;
            } else if (nums[lhs_end] < target) {
                start = lhs_end + 1;
            }
        }
        return result;
    }
};

bool test_search_range(const Numbers& nums, int target, const Numbers& expected) {
    Solution soln;
    Numbers copy(nums);
    return (soln.searchRange(copy, target) == expected);
}

void search_range_tests() {
    assert(test_search_range({}, 1, {-1,-1}));
    assert(test_search_range({1}, 1, {0,0}));
    assert(test_search_range({1,1}, 1, {0,1}));
    assert(test_search_range({1,1,1,1,1}, 1, {0,4}));
    assert(test_search_range({-1,0,1,1,1,1,1,83,123}, 1, {2,6}));
    assert(test_search_range({5,7,7,8,8,10}, 11, {-1,-1}));
    assert(test_search_range({5,7,7,8,8,10}, 5, {0,0}));
    assert(test_search_range({5,7,7,8,8,10}, 7, {1,2}));
    assert(test_search_range({5,7,7,8,8,10}, 8, {3,4}));
    assert(test_search_range({5,7,7,8,8,10}, 10, {5,5}));
}

int main(int argc, char** argv) {
    search_range_tests();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
