// Leetcode: https://leetcode.com/problems/valid-mountain-array/
// Given an array A of integers, return true if and only if it is a valid mountain array.
// A.length >= 3 and there exists 0 < i < A.length - 1 such that:
// A[0] < A[1] < ... A[i-1] < A[i] and A[i] > A[i+1] > ... > A[A.length-1]


// Brute Force:
// Better:
// Acceptance: 35.0

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 24ms. Faster than 96.12% of cpp submissions.
class Solution {
public:
  bool validMountainArray(const std::vector<int>& A) {
    if (A.size() < 3) { return false; }
    bool ascending = true;
    for (int i = 1; i < A.size(); ++i) {
      if (A[i] == A[i-1]) { return false; }
      if (ascending) {
        if (A[i] <= A[i-1]) {
          if (i < 2) { return false; }
          ascending = false;
        }
      } else {
        if (i < 2) { return false; }
        if (A[i] >= A[i-1]) { return false; }
      }
    }
    return !ascending;
  }
};

bool test_mountain_array(std::vector<int> A, bool expected) {
  Solution soln;
  return soln.validMountainArray(A) == expected;
}

void test_mountain_array() {
  assert(test_mountain_array({3}, false));
  assert(test_mountain_array({3,4}, false));
  assert(test_mountain_array({4,5,3}, true));
  assert(test_mountain_array({4,1,3}, false));
  assert(test_mountain_array({1,2,3,2,1}, true));
  assert(test_mountain_array({1,2,2,2,1}, false));
  assert(test_mountain_array({1,2,3,2,2}, false));
  assert(test_mountain_array({4,2,3,2,2}, false));
  assert(test_mountain_array({4,5,3,2,0}, true));
  assert(test_mountain_array({4,5,3,2,0,0}, false));
  assert(test_mountain_array({4,5,3,2,0,1}, false));
  assert(test_mountain_array({4,5,3,2,0,-1}, true));
  assert(test_mountain_array({9,8,7,6,5,4,3,2,1}, false));
  assert(test_mountain_array({0,1,2,3,4,5,6,7,8,9}, false));
}

int main(int argc, char** argv) {
  test_mountain_array();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
