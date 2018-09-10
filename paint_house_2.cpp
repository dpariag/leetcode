// Leetcode: https://leetcode.com/problems/paint-house-ii/description/ 
// Given n houses, k colors and an (n x k) cost matrix, find the lowest cost house coloring

// Brute Force: Generate all possible colorings, find the min O(k^n) time.
// Better: Find the best 2 colors for the N'th house, then find the best colour for
// the N-1'th house, memoizing choices as we iterate houses. O(n*k) time.

#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 8ms. Beats 73.58% of submissions.
class Solution {
public:
  int minCostII(Table& costs) {
    if (costs.empty()) { return 0; }
    int min1 = 0, min2 = 0; 
    int min1_idx = -1,  min2_idx = -1;

    for (int row = costs.size() - 1; row >= 0; --row) {
      int new_min1 = std::numeric_limits<int>::max();
      int new_min2 = std::numeric_limits<int>::max();
      int new_min1_idx = -1,  new_min2_idx = -1;
      for (int col = 0; col < costs[row].size(); ++col) {
        if (col == min1_idx) {
          costs[row][col] += min2;
        } else {
          costs[row][col] += min1;
        }

        // Find new min
        if (costs[row][col] < new_min1) {
          new_min2 = new_min1, new_min2_idx = new_min1_idx;
          new_min1 = costs[row][col], new_min1_idx = col;
        } else if (costs[row][col] < new_min2) {
          new_min2 = costs[row][col], new_min2_idx = col;
        }
      } // for
      min1 = new_min1, min2 = new_min2;
      min1_idx = new_min1_idx, min2_idx = new_min2_idx;
    }
    return min1;
  }
};

bool test_min_cost(Table costs, int expected) {
  Solution soln;
  return soln.minCostII(costs) == expected;
}

void test_min_cost() {
  assert(test_min_cost({}, 0));
  assert(test_min_cost({{4,9,2,11}}, 2));
  assert(test_min_cost({{1,5,3},{2,9,4}}, 5));
  assert(test_min_cost({{1,3,8},{2,4,1},{1,1,7}}, 3));
}

int main(int argc, char** argv) {
  test_min_cost();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
