// Leetcode: https://leetcode.com/problems/last-stone-weight/

// Brute Force:
// Better:
// Acceptance: 

#include <queue>
#include <iostream>
#include <assert.h>

using MaxHeap = std::priority_queue<int, std::vector<int>, std::less<int>>;

// Accepted. 0ms. Faster than 100.0% of submissions.
class Solution {
public:
  int lastStoneWeight(std::vector<int>& stones) {
    MaxHeap max_heap(std::less<int>(), std::move(stones));

    
    while (max_heap.size() > 1) {
      auto y = max_heap.top();
      max_heap.pop();

      auto x = max_heap.top();
      max_heap.pop();

      if (x != y) {
        max_heap.emplace(y-x);
      }
    }
    return max_heap.empty() ? 0 : max_heap.top();
  }
};

bool last_stone_weight(std::vector<int> stones, int expected) {
  Solution soln;
  return soln.lastStoneWeight(stones) == expected;
}

void last_stone_weight() {
  assert(last_stone_weight({2,2,2,2}, 0));
  assert(last_stone_weight({2,7,4,1,8,1}, 1));
}

int main(int argc, char** argv) {
  last_stone_weight();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
