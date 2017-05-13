// Leetcode: https://leetcode.com/problems/surrounded-regions/#/description
// Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.
// A region is captured by flipping all 'O's into 'X's in that surrounded region.

// Brute Force: Generate all possible regions, check if each is surrounded.
// Better:

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

using Board = std::vector<std::vector<char>>;
using Square = std::pair<int,int>; // (x,y)

// Accepted. 6ms. Beats 94.27% of submissions.
class Solution {
public:
    void bfs(Board& board, int start_x, int start_y) {
        std::deque<Square> q;
        const int num_rows = board.size();
        const int num_cols = board[0].size();

        q.emplace_back(std::make_pair(start_x, start_y));
        board[start_x][start_y] = 'R'; // Reachable
        while (!q.empty()) {
            auto& cur = q.front();
            int x = cur.first;
            int y = cur.second; 
            if (x-1 >= 0 && x-1 < num_rows && board[x-1][y] == 'O') {
                q.emplace_back(std::make_pair(x-1, y));
                board[x-1][y] = 'R'; // Square below is reachable
            }
            if (x+1 >=0 && x+1 < num_rows && board[x+1][y] == 'O') {
                q.emplace_back(std::make_pair(x+1, y));
                board[x+1][y] = 'R'; // Square above is reachable
            }

            if (y-1 >= 0 && y-1 < num_cols && board[x][y-1] == 'O') {
                q.emplace_back(std::make_pair(x, y-1));
                board[x][y-1] = 'R'; // Square to the left is reachable 
            }
            if (y+1 >= 0 && y+1 < num_cols && board[x][y+1] == 'O') {
                q.emplace_back(std::make_pair(x, y+1));
                board[x][y+1] = 'R'; // Square to the right is reachable
            }
            q.pop_front();
        }
    }

    void solve(Board& board) {
        if (board.size() < 3 || board[0].size() < 3) { return; }
        int num_rows = board.size();
        int num_cols = board[0].size();

        // Do BFS from any 'O's in the first and last rows
        for (int y = 0; y < board[0].size(); ++y) {
            if (board[0][y] == 'O') { bfs(board, 0, y); }
            if (board[num_rows-1][y] == 'O') { bfs(board, num_rows-1, y); }
        }

        // Do BFS from any 'O's in the first and last cols 
        for (int x = 0; x < board.size(); ++x) {
            if (board[x][0] == 'O') { bfs(board, x, 0); }
            if (board[x][num_cols-1] == 'O') { bfs(board, x, num_cols-1); }
        }

        // Any unreached 'O' is part of a surrounded region.
        for (int x = 0; x < board.size(); ++x) {
            for (int y = 0; y < board[x].size(); ++y) {
                if (board[x][y] == 'O') { board[x][y] = 'X'; }
                if (board[x][y] == 'R') { board[x][y] = 'O'; }
            }
        }
    }
};

Board make_board(const std::string& input, int num_cols, int num_rows) {
    Board b(num_rows, std::vector<char>(num_cols, '#'));;
    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            auto idx = row * num_cols + col;
            b[row][col] = input[idx];
        }
    }
    return b;
}

bool test_solve_board(const std::string& input, const std::string& expected, int rows, int cols) {
    Solution soln;
    auto board = make_board(input, rows, cols);
    soln.solve(board);
    auto expected_board = make_board(expected, rows, cols);
    return board == expected_board;
}

void test_solve_board() {
    assert(test_solve_board("XXXXXOOXXOOXXXOX", "XXXXXOOXXOOXXXOX", 4, 4));
    assert(test_solve_board("XXXXXOOXXXXXXXXX", "XXXXXXXXXXXXXXXX", 4, 4));
    assert(test_solve_board("XXXXXXXXXXXXXXOO", "XXXXXXXXXXXXXXOO", 4, 4));
    assert(test_solve_board("XXXXXOOXXOOXXXXX", "XXXXXXXXXXXXXXXX", 4, 4));
    assert(test_solve_board("XXXXOOOOOOOOXXXX", "XXXXOOOOOOOOXXXX", 4, 4));
    assert(test_solve_board("XXXXXOOXXXOXXXXX", "XXXXXXXXXXXXXXXX", 4, 4));
    assert(test_solve_board("OOOOOOOOOOOOOOOO", "OOOOOOOOOOOOOOOO", 4, 4));
    assert(test_solve_board("OOOOOOOOOOOOOOOO", "OOOOOOOOOOOOOOOO", 16, 1));
    assert(test_solve_board("OOOOOOOOOOOOOOOO", "OOOOOOOOOOOOOOOO", 1, 16));
}

int main(int argc, char** argv) {
    test_solve_board();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
