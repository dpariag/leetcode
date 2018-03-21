// Leetcode: https://leetcode.com/problems/battleships-in-a-board/description/

// Brute Force: Use DFS to explore the board. O(n^2) time and space
// Better: Realize that we can simply count the first (topmost/leftmost) 'X'
// in each battleship. O(n^2) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

using Board = std::vector<std::vector<char>>;

// Accepted. 8ms. Beats 88.41% of submissions, ties 30.26% of submissions.
class Solution {
public:
    int countBattleships(const Board& board) {
        if (board.empty()) { return 0; }
        int count = 0;

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == 'X') {
                    if ((i == 0 || board[i-1][j] == '.') &&
                        (j == 0 || board[i][j-1] == '.')) {
                        ++count;
                    }
                }
            }
        }
        return count;
    }
};

bool test_battleship(Board b, int expected) {
    Solution soln;
    return soln.countBattleships(b) == expected;
}

void test_battleship() {
    assert(test_battleship({{'X','X','X'},{'.','.','.'},{'.','.','.'}}, 1));
    assert(test_battleship({{'X','.','X'},{'.','.','.'},{'.','.','.'}}, 2));
    assert(test_battleship({{'X','.','.'},{'X','.','.'},{'X','.','.'}}, 1));
    assert(test_battleship({{'.','.','.'},{'.','X','.'},{'.','X','.'}}, 1));
    assert(test_battleship({{'.','.','.'},{'.','.','.'},{'.','X','X'}}, 1));
    assert(test_battleship({{'.','.','.'},{'.','.','.'},{'X','X','X'}}, 1));
    assert(test_battleship({{'X','X','X'},{'.','.','.'},{'X','X','X'}}, 2));
    assert(test_battleship({{'.','X','.'},{'.','X','.'},{'.','.','.'}}, 1));
    assert(test_battleship({{'.','X','.'},{'.','X','.'},{'.','.','X'}}, 2));
    assert(test_battleship({{'.','X','.'},{'.','X','.'},{'X','.','X'}}, 3));
}

int main(int argc, char** argv) {
    test_battleship();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}