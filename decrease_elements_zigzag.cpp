// Leetcode: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/

// Brute Force:
// Better:
// Acceptance: 

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 0ms. Faster than 100% of submissions.
class Solution {
public:
    int movesToMakeZigzag(std::vector<int>& nums) {
      int even_moves = 0, odd_moves = 0, sz = nums.size();
      for (int i = 0; i < nums.size(); ++i) {
        int left = (i - 1) >= 0 ? nums[i-1] : nums[i] + 1;
        int right = (i + 1) < sz ? nums[i+1] : nums[i] + 1;
        int smaller_neighbor = std::min(left, right);
        if (i % 2 == 0) {
          // Even
          if (nums[i] >= smaller_neighbor) even_moves += (nums[i] - smaller_neighbor + 1); 
        } else {
          // Odd
          if (nums[i] >= smaller_neighbor) odd_moves += (nums[i] - smaller_neighbor + 1);
        }
      }
      return std::min(even_moves, odd_moves);
    }
};

bool test_zig_zag(std::vector<int> nums, int expected) {
  Solution soln;
  return soln.movesToMakeZigzag(nums) == expected;
}

void test_zig_zag() {
  assert(test_zig_zag({1,2,3}, 2));
  assert(test_zig_zag({1,2,1}, 0));
  assert(test_zig_zag({9,6,1,6,2}, 4));
  assert(test_zig_zag({10,12,15,16,0}, 4));
  assert(test_zig_zag({1,2,1,10,1,11,1,2}, 0));
  assert(test_zig_zag({2,1,10,1,11,1,2}, 0));
  assert(test_zig_zag({10,4,4,10,10,6,2,3}, 13));
}

int main(int argc, char** argv) {
  test_zig_zag();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
