// Leetcode: https://leetcode.com/problems/largest-number-at-least-twice-of-others/
// Find whether the largest element in the array is at least twice as much as every other number in the array.

// Brute Force: Make one pass of the array to find the max, another to see if it is twice as big as every other elem
// Better: Simplify to one pass by finding the largest and 2nd largest element. Compare those two.
// Acceptance: 40.1

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 4ms. Beats 99.10% of cpp submissions.
class Solution {
public:
  int dominantIndex(const std::vector<int>& nums) {
    int max = -1, max_2 = -1;
    int max_index = -1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] > max) {
        max_2 = max;
        max = nums[i];
        max_index = i;
      } else if (nums[i] > max_2) {
        max_2 = nums[i];
      }
    }
    return (max >= 2*max_2) ? max_index : -1;
  }
};

void test_dominant_index() {
  Solution soln;
  assert(soln.dominantIndex({1}) == 0);
  assert(soln.dominantIndex({0,0,3,2}) == -1);
  assert(soln.dominantIndex({3,6,1,0}) == 1);
  assert(soln.dominantIndex({1,2,3,4}) == -1);
}

int main(int argc, char** argv) {
  test_dominant_index();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
