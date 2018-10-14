// Leetcode: https://leetcode.com/problems/random-pick-with-weight/
// Given w[i] where w[i] > 0 and w[i] describes the weight of index i, randomly pick an index in 
// proportion to its weight.

// Approach: Build an array of cumulative sums, then generate a random number. Use binary search
// to find the index i such that sums[i-1] <= rand < sums[i]

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted.  104ms. Beats 73.30% of submissions.
class Solution {
public:
  Solution(const std::vector<int>& w): sum(0), sums(w.size(), 0) {
    for (int i = 0; i < w.size(); ++i) {
      sum += w[i];
      sums[i] = sum;
    }      
  }

  int pickIndex() {
    int rand = std::rand() % sum;
    int left = 0, right = sums.size() - 1, mid = 0;
    while (left < right) {
      mid = left + (right - left) / 2;
      if (rand < sums[mid] && (mid == 0 || rand >= sums[mid-1])) {
        return mid;
      } else if (rand < sums[mid]) {
        right = mid - 1;
      } else if (rand >= sums[mid]) {
        left = mid + 1;
      }
    }
    return left;
  }
private:
  int sum;
  std::vector<int64_t> sums;
};

int main(int argc, char** argv) {
  std::srand(std::time(nullptr));
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
