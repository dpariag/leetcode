// Leetcode: https://leetcode.com/problems/n-queens/?tab=Description 
// Given an integer n, return all distinct solutions to the n-queens puzzle. A solution is a
// placement of all n-queens, such that no queen attacks any other queen.
// The board is represented using characters: 'Q' and '.' indicate a queen and an empty space 
// respectively. For example, There exist two distinct solutions to the 4-queens puzzle:
// [[".Q..",  // Solution 1   ["..Q.",  // Solution 2
//   "...Q",                   "Q...",
//   "Q...",                   "...Q",
//   "..Q."],                  ".Q.."]]

// Brute Force: Try all possible queen placements, evaluate the board for attacking queens.
// Better: Recursive backtracking. Try to make attack evaluation cheap.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Represent valid solutions using vectors of strings
using ValidBoard = std::vector<std::string>;
using ValidBoards = std::vector<ValidBoard>;

class BoardState {
public:
    BoardState(int n): 
        m_offset(n-1), m_rows(n, false), m_cols(n,false), 
        m_lr_diag(n, false), m_rl_diag(n,false) {}

    // There are 16 diagonals (0..15) in each direction
    inline bool is_attacked(int row, int col) const {
        return m_rows[row] || m_cols[col] || m_lr_diag[row-col+m_offset] || m_rl_diag[row+col];
    } 

    inline void place_queen(int row, int col) {
        m_rows[row] = true;
        m_cols[col] = true;
        m_lr_diag[row-col+m_offset] = true;
        m_rl_diag[row+col] = true;
    }

    inline void remove_queen(int row, int col) {
        m_rows[row] = false;
        m_cols[col] = false;
        m_lr_diag[row-col+m_offset] = false;
        m_rl_diag[row+col] = false;
    }

private:
    int m_offset;
    std::vector<bool> m_rows;
    std::vector<bool> m_cols;
    std::vector<bool> m_lr_diag; // top-left to bottom-right diagonals (x-y+7)
    std::vector<bool> m_rl_diag; // top-right to bottom-left diagonals (x+y)
}; 

// Accepted. 6ms. Beats 42.14% of submissions, ties 39.31%
class Solution {
public:
    void n_queens(int n, int cur_row, ValidBoard& board, ValidBoards& valid, BoardState& state) {
        if (cur_row >= n) {
            valid.emplace_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            if (!state.is_attacked(cur_row, col)) {
                state.place_queen(cur_row, col);
                board[cur_row][col] = 'Q';
                n_queens(n, cur_row + 1, board, valid, state);
                state.remove_queen(cur_row, col);
                board[cur_row][col] = '.';
            }
        }

    } 

    ValidBoards solveNQueens(int n) {
        ValidBoards valid;
        ValidBoard board(n, std::string(n, '.'));
        BoardState state(n);
        n_queens(n, 0, board, valid, state);
        return valid;
    }
};

// No testing yet.

int main(int argc, char** argv) {
    Solution s;
    s.solveNQueens(9);
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
