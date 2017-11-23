// Leetcode: https://leetcode.com/problems/flip-game-ii/description/
// Given a string that contains only '+' and '-' chars, you and your friend take turns flipping
// consecutive "++" into "--". The game ends when a player can no longer make a flip.
// Determine if the starting player can guarantee a win.

#include <string>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Cache = std::unordered_map<std::string, bool>;

// Start 1:45pm
// End: 1:53pm
// Accepted. 219ms. Beats 12.90% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool check_can_win(std::string& s, Cache& cache) {
      auto found = cache.find(s);
      if (found != cache.end()) { return found->second; }

      int i = 0;
      while (i+1 < int(s.size())) {
          if (s[i] == '+' && s[i+1] == '+') {
            // Found a move
            s[i] = s[i+1] = '-';
            if (!canWin(s)) {
              s[i] = s[i+1] = '+';  
              cache.emplace(s, true);
              return true;
            }
            s[i] = s[i+1] = '+';
          }
          i += (s[i+1] == '-' ? 2 : 1);
      }
      cache.emplace(s, false);
      return false;
    }

    bool canWin(std::string& s) {
      Cache cache;
      return check_can_win(s, cache);  
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}