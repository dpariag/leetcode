// Leetcode: https://leetcode.com/problems/game-of-life/description/

// Brute Force: Allocate a new board and calculate the state of each square based on the new board.
// Better: Update the board in place by using upper bits of each cell to store the next state
// while keeping the current state intact.

#include <vector>
#include <iostream>
#include <assert.h>

using Board = std::vector<std::vector<int>>;

// Accepted. 3ms. Beats 3.44% of submissions, ties 68.48% of submissions
class Solution {
public:
    const int DEAD = 0;
    const int LIVE = 1;    

    inline int get_value(const Board& board, int row, int col) {
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size()) { return 0; }
        return board[row][col] & 3; // return lower 2 bits
    }

    inline int next_state(int cur_state, int live_neighbors) {
        if (cur_state == LIVE) {
            if (live_neighbors < 2 || live_neighbors > 3) { return DEAD; }
            return LIVE;
        } else if (cur_state == DEAD) {
            if (live_neighbors == 3) { return LIVE; }
            return DEAD;
        }
        return DEAD;
    }

    int get_live_neighbors(const Board& board, int row, int col) {
        int num_alive = 0;
        num_alive += get_value(board, row-1, col-1);
        num_alive += get_value(board, row-1, col);
        num_alive += get_value(board, row-1, col+1);
        num_alive += get_value(board, row, col-1);
        num_alive += get_value(board, row, col+1);
        num_alive += get_value(board, row+1, col-1);
        num_alive += get_value(board, row+1, col);
        num_alive += get_value(board, row+1, col+1);
        return num_alive;
    }

    void gameOfLife(Board& board) {
        // Add next state for each square
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                auto live_neighbors = get_live_neighbors(board, row, col);
                board[row][col] |= (next_state(board[row][col], live_neighbors) << 2);
            }
        }

        // Discard old state for each square
        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col) {
                board[row][col] >>= 2;
            }
        }
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
