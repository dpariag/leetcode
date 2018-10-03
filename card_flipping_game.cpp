// Leetcode: https://leetcode.com/problems/card-flipping-game/description/
// You are given two arrays representing the numbers on the front and back of cards respectively.
// Cards may be flipped, exchanging the front and back values of the card.
// Find the smallest number that can appear on the back of one card and on the front of none.

// Approach: Scan cards to find any card with same number on front and back ('good' cards)
// Then scan the cards to find the smallest number that is good. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 12ms. Beats 97.70% of cpp submissions.
class Solution {
  public:
    int flipgame(std::vector<int>& fronts, std::vector<int>& backs) {
      std::vector<bool> good(2001, true);
      for (int i = 0; i < fronts.size(); ++i) {
        if (fronts[i] == backs[i]) {
          good[fronts[i]] = false;
        }
      }
     
      int min_good = std::numeric_limits<int>::max(); 
      for (int i = 0; i < fronts.size(); ++i) {
        auto min = std::min(fronts[i], backs[i]);
        auto max = std::max(fronts[i], backs[i]);
        if (good[min]) {
          min_good = std::min(min_good, min);
        } else if (good[max]) {
          min_good = std::min(min_good, max);
        }
      }
      return min_good == std::numeric_limits<int>::max() ? 0 : min_good;
    }
};

using Cards = std::vector<int>;
bool test_flip_game(Cards fronts, Cards backs, int expected) {
  Solution soln;
  return soln.flipgame(fronts, backs) == expected;
}

void test_flip_game() {
  assert(test_flip_game({1,2,4,4,7},{1,3,4,1,3}, 2));
}

int main(int argc, char** argv) {
  test_flip_game();  
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
