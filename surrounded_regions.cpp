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
struct Square {
    int x;
    int y;
    Square(int x_cood, int y_cood): x(x_cood), y(y_cood) {}
};

void print(const Board& b) {
    for (int row = 0; row < b.size(); ++row) {
        for (int col = 0; col < b[row].size(); ++col) {
            std::cout << b[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

class Solution {
public:
    inline bool is_valid(const Board& board, int x, int y) {
        return (x >= 0 && x < board.size() && y >= 0 && 
                y < board.front().size() && 
                board[x][y] == 'O');
    }

    void bfs(Board& board, int x, int y) {
        std::queue<Square> q;

        q.emplace(Square(x,y));
        while (!q.empty()) {
            auto cur = q.front();
            //std::cout << "Exploring " << cur.x << "," << cur.y << std::endl;
            board[cur.x][cur.y] = 'R'; // Reachable
            if (is_valid(board, cur.x-1, cur.y)) { q.emplace(Square(cur.x-1, cur.y)); }
            if (is_valid(board, cur.x+1, cur.y)) { q.emplace(Square(cur.x+1, cur.y)); }
            if (is_valid(board, cur.x, cur.y-1)) { q.emplace(Square(cur.x, cur.y-1)); }
            if (is_valid(board, cur.x, cur.y+1)) { q.emplace(Square(cur.x, cur.y+1)); }
            q.pop();
        }
    }

    void solve(Board& board) {
        if (board.size() < 3 || board[0].size() < 3) { return; }
        for (int x = 0; x < board.size(); ++x) {
            if (board[x].front() == 'O') { bfs(board, x, 0); }
            if (board[x].back() == 'O') { bfs(board, x, board[x].size() - 1); }
        }

        for (int y = 0; y < board[0].size(); ++y) {
            if (board.front()[y] == 'O') { bfs(board, 0, y); }
            if (board.back()[y] == 'O') { bfs(board, board.size() - 1, y); }
        }

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
    //std::cout << std::endl;
    //print(board);
    soln.solve(board);
    //std::cout << std::endl << std::endl;
    //print(board);
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
    assert(test_solve_board("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO", "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO", 200, 1));
}

int main(int argc, char** argv) {
    test_solve_board();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
