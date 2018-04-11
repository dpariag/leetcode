// Leetcode: https://leetcode.com/problems/valid-sudoku/description/
// Determine if a 9x9 sudoku board is valid (None of 1-9 can be reused in any row, col, or sub-grid).

// Brute Force: Three passes, checking rows, then cols, then sub-grids
// Better: One pass with state to track the use of 1-9 in each row, col, and sub-grid.

#include <vector>
#include <iostream>
#include <assert.h>

using Board = std::vector<std::vector<char>>;
using Used = std::vector<std::vector<bool>>;

// Accepted. 23ms. Beats 63.28% of submissions.
class Solution {
public:
    bool isValidSudoku(Board& board) {
        Used row_used(9, std::vector<bool>(9, false));
        Used col_used(9, std::vector<bool>(9, false));
        Used grid_used(9, std::vector<bool>(9, false));

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '.') continue;
                int value = board[row][col] - '0';                
                int grid = (row/3) * 3 + (col/3);
                if (row_used[row][value-1] || col_used[col][value-1] || grid_used[grid][value-1]) {
                    return false;
                }
                row_used[row][value-1] = true;
                col_used[col][value-1] = true;
                grid_used[grid][value-1] = true;
            }
        }
        return true;
    }
};

bool test_sudoku(Board b, bool expected) {
    Solution soln;
    return soln.isValidSudoku(b) == expected;
}

void test_sudoku() {
    assert(test_sudoku({{'1','6','.','.','.','.','.','.','.'},
                        {'8','7','.','.','.','.','.','.','.'},
                        {'3','4','.','.','.','.','.','.','.'},
                        {'6','5','.','.','.','.','.','.','.'},
                        {'4','8','.','.','.','.','.','.','.'},
                        {'9','2','.','.','.','.','.','.','.'},
                        {'7','1','.','.','.','.','.','.','.'},
                        {'5','9','.','.','.','.','.','.','.'},
                        {'2','3','.','.','.','.','.','.','.'}
                    }, true));
}

int main(int argc, char** argv) {
    test_sudoku();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
