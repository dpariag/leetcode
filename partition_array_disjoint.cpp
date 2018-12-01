// Leetcode: https://leetcode.com/problems/partition-array-into-disjoint-intervals/submissions/
// Given an array A, partition it into two subarrays [left,right] such that every element in left is
// less than or equal to every element in right.

// Brute Force:
// Better:
// Acceptance: 40.4

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 28ms. Beats 97.47% of cpp submissions
class Solution {
public:
  int partitionDisjoint(std::vector<int>& A) {
    std::vector<int> mins(A.size(), A.back());
    for (int i = A.size() - 2; i >= 0; --i) {
      mins[i] = std::min(A[i], mins[i+1]);
    }

    int max = A.front();
    for (int i = 0; i < A.size()-1; ++i) {
      max = std::max(max, A[i]);
      if (max <= mins[i+1]) {
        return i+1;
      }
    }
    return 0;
  }
};

bool test_partition(std::vector<int> A, int expected) {
  Solution soln;
  return soln.partitionDisjoint(A) == expected;
}

void test_partition() {
  assert(test_partition({5,5}, 1));
  assert(test_partition({5,6}, 1));
  assert(test_partition({10,11,3,0,6,15,10,20}, 7));
  assert(test_partition({5,0,3,8,6}, 3));
  assert(test_partition({1,1,1,0,6,12}, 4));
}

int main(int argc, char** argv) {
  test_partition();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
