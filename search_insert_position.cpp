// Leetcode: https://leetcode.com/problems/search-insert-position/
// Given a sorted integer array and a target value, return the index of the target in the array. 
// If the target does not exist in the array, return the index where it should be inserted to preserve sorted order.

// Brute Force:
// Better:
// Acceptance: 40.3

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 4ms. Faster than 99.81% of submissions.
class Solution {
public:
  int searchInsert(const std::vector<int>& nums, int target) {
    if (nums.empty()) { return 0; }
    int left = 0, right = nums.size() - 1;
    int mid = left;
    while (left <= right) {
      mid = left + (right - left) / 2;
      if (nums[mid] == target) {
        return mid;
      } else if (left == right) {
        break;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        // nums[mid] > target
        right = mid - 1;
      }
    } // while
    return target < nums[mid] ? mid : mid + 1;
  }
};

void test_search_insert() {
  Solution soln;
  assert(soln.searchInsert({1,3,5,6}, 1) == 0);
  assert(soln.searchInsert({1,3,5,6}, 3) == 1);
  assert(soln.searchInsert({1,3,5,6}, 5) == 2);
  assert(soln.searchInsert({1,3,5,6}, 6) == 3);
  assert(soln.searchInsert({1,3,5,6}, 2) == 1);
  assert(soln.searchInsert({1,3,5,6}, 0) == 0);
  assert(soln.searchInsert({1,3,5,6}, 7) == 4);
  assert(soln.searchInsert({1,3,7,11}, 4) == 2);
  assert(soln.searchInsert({1,3,7,11}, 9) == 3);
}

int main(int argc, char** argv) {
  test_search_insert();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
