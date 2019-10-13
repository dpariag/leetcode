// Leetcode: https://leetcode.com/problems/bag-of-tokens/

// Approach: Sort tokens, use the smallest/leftmost tokens to gain points, and the largest/rightmost to gain power.
// Acceptance: 38.3

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 4ms. Beats 100% of cpp submissions.
class Solution {
public:
  int bagOfTokensScore(std::vector<int>& tokens, int power) {
    int points = 0, max_points = 0;
    int left = 0, right = tokens.size() - 1;
    std::sort(tokens.begin(), tokens.end());
    
    while (left <= right) {
      if (tokens[left] <= power) {
        power -= tokens[left];
        ++points, ++left;
      } else if (points > 0) {
        power += tokens[right];
        --points, --right;
      } else {
        break;
      }
      max_points = std::max(max_points, points);
    }
    return max_points;
  }
};

bool test_tokens(std::vector<int> tokens, int power, int expected) {
  Solution soln;
  return soln.bagOfTokensScore(tokens, power) == expected;
}

void test_tokens() {
  assert(test_tokens({100}, 50, 0));
  assert(test_tokens({100,200}, 150, 1));
  assert(test_tokens({100,200,300,400}, 200, 2));
}

int main(int argc, char** argv) {
  test_tokens();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
