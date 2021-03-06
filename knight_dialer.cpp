// Leetcode: https://leetcode.com/problems/knight-dialer/
// Determine how many unique numbers can be generated by a chess knight on a phone number pad.

// Brute Force: Recursively enumerate all possible numbers from every starting point. Exponential time.
// Better: Pre-calculate the moves possible from every starting number. Build a DP table of the number of unique
// numbers generated with K moves from each starting position. The recurrence follows naturally. O(N) time and space.
// Acceptance: 37.5

#include <iostream>
#include <vector>
#include <assert.h>

using Moves = std::vector<std::vector<int>>;
Moves g_moves = {{4,6}, {6,8}, {7,9}, {4,8}, {0,3,9}, {}, {0,1,7}, {2,6}, {1,3}, {2,4}};

const int g_numRows = 5001;
const int g_numCols = 10;

// Accepted. 84ms. Faster than 79.41% of cpp submissions
class Solution {
public:
    int knightDialer(int N) {
      int table[g_numRows][g_numCols] = {{0}};
      for (int col = 0; col < g_numCols; ++col) { table[1][col] = 1; }

      int total_moves = 10;
      for (int row = 2; row <= N; ++row) {
        total_moves = 0;
        for (int col = 0; col < g_numCols; ++col) {
          for (const auto move : g_moves[col]) {
            table[row][col] = (table[row][col] + table[row-1][move]) % 1000000007;
          }
          total_moves = (total_moves + table[row][col]) % 1000000007;
        }
      }
      return total_moves;
    }
};

void test_knight_dialer() {
  Solution soln;
  assert(soln.knightDialer(1) == 10);
  assert(soln.knightDialer(2) == 20);
  assert(soln.knightDialer(3) == 46);
}

int main(int argc, char** argv) {
  test_knight_dialer();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
