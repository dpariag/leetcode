// Leetcode: https://leetcode.com/problems/find-pivot-index/
// Given an integer array, return an index i such that sum(0,i-1) == sum(i+1,n-1)

// Brute Force: For each i, calculate left and right sums then check for equality. O(n^2)
// Better: Calculate prefix and suffix sums then scan them for a valid partition. O(n) time.
// Acceptance: 39.7

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 24ms. Faster than 98.02% of cpp submissions.
class Solution {
public:
  int pivotIndex(const std::vector<int>& nums) {
    if (nums.empty()) { return -1; }
    std::vector<int> prefix_sums(nums.size(), 0);
    std::vector<int> suffix_sums(nums.size(), 0);
    
    prefix_sums.front() = nums.front();
    suffix_sums.back() = nums.back(); 
    auto last_idx = nums.size() - 1;
    for (int i = 1; i < nums.size(); ++i) {
      prefix_sums[i] = prefix_sums[i-1] + nums[i];
      auto right = last_idx - i;
      suffix_sums[right] = suffix_sums[right + 1] + nums[right];
    }
 
    for (int i = 0; i < nums.size(); ++i) {
      int left_sum = (i == 0) ? 0 : prefix_sums[i-1];
      int right_sum = (i == last_idx) ? 0 : suffix_sums[i+1];
      if (left_sum == right_sum) { return i; }
    }    
    return -1;
  }
};

bool test_pivot_index(std::vector<int> nums, int expected) {
  Solution soln;
  return soln.pivotIndex(nums) == expected;
}

void test_pivot_index() {
  assert(test_pivot_index({}, -1));
  assert(test_pivot_index({1,2,1}, 1));
  assert(test_pivot_index({1,2,3}, -1));
  assert(test_pivot_index({2,2,1,1}, 1));
  assert(test_pivot_index({1,2,-2,1,-1}, 0));
  assert(test_pivot_index({2,1,-2,-1,11}, 4));
  assert(test_pivot_index({2,1,-2,1,0,0,1}, 3));
}

int main(int argc, char** argv) {
  test_pivot_index();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
