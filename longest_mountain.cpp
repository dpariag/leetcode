// Leetcode: https://leetcode.com/problems/longest-mountain-in-array/description/
// Given an array A of integers, return the length of the longest mountain. 
// A mountain is a subarray B where B[0] < B[1] < .. < B[k] > B[k+1] > ... > B[m] and B.length >= 3

// Brute Force: Generate all subarrays, check if each is a mountain. O(n^3) time.
// Better: Use a state machine to track a rising subarray followed by a falling subarray. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 12ms. Beats 97.14% of submissions.
class Solution {
public:
  int longestMountain(std::vector<int>& A) {
    bool rising = true;
    int i = 1, max_length = 0, rising_length = 1, falling_length = 0;

    while (i < A.size()) {
      if (rising) {
        // Rising
        if (A[i] > A[i-1]) {
          ++rising_length;
        } else if (A[i] < A[i-1]) {
          rising = false;
          ++falling_length;
        } else {
          rising_length = 1;
        }
      } else {
        // Falling
        if (A[i] < A[i-1]) {
          ++falling_length;
        } else if (A[i] > A[i-1]) {
          rising = true;
          rising_length = 2, falling_length = 0;
        } else {
          rising = true;
          rising_length = 1, falling_length = 0;
        }
      }
      if (rising_length >= 2 && falling_length >= 1) {
        max_length = std::max(max_length, rising_length + falling_length);
      }
      ++i;
    } // while
    return max_length;
  }
};

bool test_longest_mountain(std::vector<int> A, int expected) {
  Solution soln;
  return soln.longestMountain(A) == expected;
}

void test_longest_mountain() {
  assert(test_longest_mountain({2,2,2}, 0));
  assert(test_longest_mountain({2,2,2,3,1}, 3));
  assert(test_longest_mountain({1,4,7,3,2,5}, 5));
  assert(test_longest_mountain({1,1,0,0,1,0}, 3));
  assert(test_longest_mountain({2,3,3,2,0,2}, 0));
  assert(test_longest_mountain({2,1,4,7,3,2,5}, 5));
  assert(test_longest_mountain({2,2,2,3,1,2,3,4,5,0}, 6));
  assert(test_longest_mountain({0,1,2,3,4,5,6,7,8,9}, 0));
  assert(test_longest_mountain({0,0,1,0,0,1,1,1,1,1}, 3));
  assert(test_longest_mountain({2,2,2,3,4,10,12,9,8,7,0}, 9));
  assert(test_longest_mountain({2,2,2,3,4,10,12,9,8,7,0,100}, 9));
}

int main(int argc, char** argv) {
  test_longest_mountain();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
