// Leetcode: https://leetcode.com/problems/previous-permutation-with-one-swap/
// Given an array A of positive integers (not necessarily distinct), return the lexicographically largest 
// permutation that is smaller than A, that can be made with one swap (A swap exchanges the positions of 
// two numbers A[i] and A[j]). If it cannot be done, then return the same array.
// 1 <= A.length <= 10000
// 1 <= A[i] <= 10000

// Brute Force:
// Better:
// Acceptance: 46.9

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 108ms. Faster than 91.28% of C++ submissions.
class Solution {
public:
  std::vector<int> prevPermOpt1(std::vector<int>& A) {
    // Two pass algorithm
    // 1: Scan right to left looking for the first element, A[x], not in ascending order
    int x = -1;
    for (int i = A.size() - 1; i > 0; --i) {
      if (A[i] < A[i-1]) {
        x = (i-1);
        break;
      }
    }
    
    if (x == -1) {
      return A;
    }   
 
    // 2: Scan right to left looking for the largest element, A[y] that is smaller than A[x].
    int y = A[x];
    for (int i = A.size() - 1; i > 0; --i) {
      if (A[i] < A[x]) {
        y = i;
        break;
      }
    }

    // Take the leftmost instance of A[y]
    while (y > 0 && A[y-1] == A[y]) --y;

    // 3: Swap X and Y
    std::swap(A[x], A[y]);
    // for (auto a : A) std::cout << a << ",";
    // std::cout << std::endl;
    return A;
  }
};

bool test_permutation(std::vector<int> arr, std::vector<int> expected) {
  Solution soln;
  return soln.prevPermOpt1(arr) == expected;
}

void test_permutation() {
  assert(test_permutation({3,1,1,3}, {1,3,1,3}));
  assert(test_permutation({4,3,2,1}, {4,3,1,2}));
  assert(test_permutation({4,5,8,2}, {4,5,2,8}));
  assert(test_permutation({5,6,1,3,4,9}, {5,4,1,3,6,9}));
  assert(test_permutation({1,2,3,4}, {1,2,3,4}));
}

int main(int argc, char** argv) {
  test_permutation();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
