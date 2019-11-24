// Leetcode: https://leetcode.com/problems/alphabet-board-path/

// Brute Force:
// Better:
// Acceptance: 44.7

#include <iostream>
#include <string>
#include <assert.h>

using Cood = std::pair<int, int>; // <row, column>

inline void move_horizontal(int moves, std::string& result) {
  char append = (moves < 0) ? 'L' : 'R';
  result.append(std::abs(moves), append);
}

inline void move_vertical(int moves, std::string& result) {
  char append = (moves < 0) ? 'U' : 'D';
  result.append(std::abs(moves), append);
}

// Accepted. 0ms. Faster than 100% of submissions.
class Solution {
public:
  std::string alphabetBoardPath(const std::string& target) {
    std::string result;
    char pos = 'a';

    for (auto ch : target) {
      auto cur_pos = coods[pos-'a'];
      auto next_pos = coods[ch-'a'];
    
      if (pos == 'z') {
        move_vertical(next_pos.first - cur_pos.first, result);
        move_horizontal(next_pos.second- cur_pos.second, result);
      } else {
        move_horizontal(next_pos.second- cur_pos.second, result);
        move_vertical(next_pos.first - cur_pos.first, result);
      } 
      result.append(1, '!');
      pos = ch; 
    }
    return result;
  }
  
  Cood  coods[26] = {
    {0,0}, {0,1}, {0,2}, {0,3}, {0,4},
    {1,0}, {1,1}, {1,2}, {1,3}, {1,4},
    {2,0}, {2,1}, {2,2}, {2,3}, {2,4},
    {3,0}, {3,1}, {3,2}, {3,3}, {3,4},
    {4,0}, {4,1}, {4,2}, {4,3}, {4,4},
    {5,0}
  };
};

bool test_alphabet_board(std::string target, std::string expected) {
  Solution soln;
  return soln.alphabetBoardPath(target) == expected;
}

void test_alphabet_board() {
  assert(test_alphabet_board("zb", "DDDDD!UUUUUR!"));
  assert(test_alphabet_board("zdz", "DDDDD!UUUUURRR!LLLDDDDD!"));
  assert(test_alphabet_board("leet", "RDD!RRRUU!!DDD!"));
  assert(test_alphabet_board("code", "RR!RRDD!LUU!R!"));
}

int main(int argc, char** argv) {
  test_alphabet_board();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
