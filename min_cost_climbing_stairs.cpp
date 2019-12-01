// Leetcode: https://leetcode.com/problems/min-cost-climbing-stairs/

// Brute Force: Generate all paths, cost each and choose the min. O(2^n) time.
// Better: DP approach. min_cost[i] stores the cheapest way to get to i'th step.
// See below for the recurrence.
// Acceptance: 48.5

#include <iostream>
#include <vector>
#include <assert.h>

// Accepted. 4ms. Faster than 98.29% of cpp submissions.
class Solution {
public:
  int minCostClimbingStairs(std::vector<int>& cost) {
    std::vector<int> min_cost(cost.size()+1, 0);
    for (int i = 2; i < min_cost.size(); ++i) {
      min_cost[i] = std::min(min_cost[i-1] + cost[i-1], min_cost[i-2] + cost[i-2]);
    }
    return min_cost.back();
  }
};

bool test_min_cost(std::vector<int> cost, int expected) {
  Solution soln;
  return soln.minCostClimbingStairs(cost) == expected;
}

void test_min_cost() {
  assert(test_min_cost({10,15}, 10));
  assert(test_min_cost({10,15,20}, 15));
  assert(test_min_cost({10,15,20,1}, 16));
  assert(test_min_cost({1, 100, 1, 1, 1, 100, 1, 1, 100}, 5));
  assert(test_min_cost({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, 6));
}

int main(int argc, char** argv) {
  test_min_cost();
  test_min_cost();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
