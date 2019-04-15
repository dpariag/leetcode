// Leetcode: https://leetcode.com/problems/minimum-increment-to-make-array-unique/

// Brute Force: For each value, scan the array looking for a duplicate, increment and repeat.
// Better: Count values using an array/hashmap. Use two indices to scan the array. The left finds duplicates
// and the right finds unused values.
// Acceptance: 42.3 

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 64ms. Faster than 98.19% of submissions.
class Solution {
public:
  int minIncrementForUnique(const std::vector<int>& A) {
    const int MAX_VALUE = 40000;
    int counts[MAX_VALUE+1] = {0};

    // Count all values
    for (int i = 0; i < A.size(); ++i) {
      ++counts[A[i]];
    }

    // Scan the counted values calculating number of moves required
    int left = 0, right = 0, moves = 0;
    while (right < MAX_VALUE) {
      while (left < MAX_VALUE && counts[left] <= 1) ++left; // Find a non-unique value
      right = std::max(left, right);
      while (right < MAX_VALUE && counts[right] != 0) ++right; // Find a gap on the right
      moves += (right - left);
      counts[right]++;
      counts[left]--;
    } 

    // We may still have non-unique values
    ++right;
    while (left < MAX_VALUE) {
      if (counts[left] > 1) {
        moves += (right - left);
        ++right;
        --counts[left];
      } else {
        ++left;
      }
    }
    return moves;
  }
};

void test_min_increment() {
  Solution soln;

  assert(soln.minIncrementForUnique({5,5,7,7}) == 2);
  assert(soln.minIncrementForUnique({1,2,2}) == 1);
  assert(soln.minIncrementForUnique({1,1,1}) == 3);
  assert(soln.minIncrementForUnique({1,1,1,3}) == 4);
  assert(soln.minIncrementForUnique({1,1,1,3,3}) == 6);
  assert(soln.minIncrementForUnique({3,2,1,2,1,7}) == 6);
}

int main(int argc, char** argv) {
  test_min_increment();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
