// Leetcode: https://leetcode.com/problems/advantage-shuffle/
// Given two arrays A and B, return a permutation of A that maximizes the 'advantage' of A.
// The advantage of A is the number of A[i] such that A[i] > B[i].

// Brute Force: Generate all possible permutation of A, check which maximizes the advantage. O(n!) time.
// Better: For each B[i], use a BST to choose the smallest A[j] that is larger than B[i]. O(n*logn) time.
// Acceptance: 40.5

#include <set>
#include <vector>
#include <iostream>
#include <assert.h>
#include "debug.h"

// Accepted. 124ms. Faster than 89.81% of submissions
class Solution {
public:
  std::vector<int> advantageCount(std::vector<int>& A, std::vector<int>& B) {
    std::multiset<int> sorted_A;
    for (int i = 0; i < A.size(); ++i) {
      sorted_A.emplace(A[i]);
      A[i] = -1;
    }    

    for (int i = 0; i < B.size(); ++i) {
      auto bigger = sorted_A.upper_bound(B[i]);
      if (bigger == sorted_A.end()) bigger = sorted_A.begin();
      A[i] = *bigger;
      sorted_A.erase(bigger);
    }
    return A; 
  }
};

bool test_advantage_shuffle(std::vector<int> A, std::vector<int> B, std::vector<int> shuffle) {
  Solution soln;
  return soln.advantageCount(A, B) == shuffle;
}

void test_advantage_shuffle() {
  assert(test_advantage_shuffle({2,7,11,15},{1,10,4,11},{2,11,7,15})); 
  assert(test_advantage_shuffle({12,24,8,32},{13,25,32,11},{24,32,8,12})); 
}

int main(int argc, char** argv) {
  test_advantage_shuffle();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
