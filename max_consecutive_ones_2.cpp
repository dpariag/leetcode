// Leetcode: https://leetcode.com/problems/max-consecutive-ones-ii/
// Given a binary array, find the maximum number of consecutive 1s if you can flip at most one 0.

// Acceptance: 45.8
// Approach: Scan left to right keeping track of the current state of the scan:
// - scanning a first block of ones
// - scanning a block of zeroes (one or more)
// - scanning a second block of ones
// O(n) time and O(1) space

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 24ms. Faster than 98.56% of submissions
class Solution {
public:
  int findMaxConsecutiveOnes(const std::vector<int>& nums) {
    int first_ones = 0, second_ones = 0, num_zeroes = 0;
    int max_consecutive = 0;

    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 1) {
        if (num_zeroes == 0) {
          first_ones += 1;
        } else {
          second_ones += 1;
        }
      } else {
        if (num_zeroes == 0) {
          num_zeroes = 1;
        } else {
          // Already have a zero
          if (num_zeroes == 1 && second_ones > 0) {
            first_ones = second_ones, second_ones = 0;
          } else {
            first_ones = 0, second_ones = 0, num_zeroes = 0;
          }
        } 
      }
      max_consecutive = std::max(max_consecutive, first_ones + second_ones + num_zeroes);
    } // for
    return max_consecutive;
  }
};

bool test_max_consecutive(std::vector<int> nums, int expected) {
  Solution soln;
  return soln.findMaxConsecutiveOnes(nums) == expected;
}

void test_max_consecutive() {
  assert(test_max_consecutive({0}, 1));
  assert(test_max_consecutive({1}, 1));
  assert(test_max_consecutive({0,1}, 2));
  assert(test_max_consecutive({1,0}, 2));
  assert(test_max_consecutive({0,0,0}, 1));
  assert(test_max_consecutive({1,1,1}, 3));
  assert(test_max_consecutive({0,0,0,0}, 1));
  assert(test_max_consecutive({0,1,0,1,0,1}, 3));
  assert(test_max_consecutive({0,0,1,1,1,0,1,1}, 6));
  assert(test_max_consecutive({1,1,1,0,1,1,1,1}, 8));
  assert(test_max_consecutive({1,1,1,0,0,1,1,1,1}, 4));
  assert(test_max_consecutive({0,0,1,1,1,0,0,1,1}, 4));
  assert(test_max_consecutive({1,0,0,1,0,0,1,0,1}, 3));
  assert(test_max_consecutive({1,1,1,0,1,1,1,1,0,1}, 8));
  assert(test_max_consecutive({1,0,1,1,1,1,0,1,1,1,1}, 9));
  assert(test_max_consecutive({1,1,1,1,1,1,1,1,1,1,0}, 11));
  assert(test_max_consecutive({1,1,1,1,1,1,1,1,1,1,0,0,0}, 11));
}

int main(int argc, char** argv) {
  test_max_consecutive();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
