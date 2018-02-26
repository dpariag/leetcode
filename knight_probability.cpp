// Leetcode: https://leetcode.com/problems/knight-probability-in-chessboard/description/
// Given an NxN chessboard and the starting position for a knight, determine the probability
// that the knight is still on the board after K moves.

// Brute Force: Use DFS to count valid moves for the next K moves, then calculate probability.
// Better: Use DFS, but memoize the number of valid moves using table[row][col][k].

#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>

using Move = std::pair<int, int>;
using Moves = std::vector<Move>;
using Table = std::vector<std::vector<std::vector<double>>>;

// Accepted. 10ms. Beats 28.47% of submissions, ties < 1% of submissions.
class Solution {
public:

    inline bool is_valid(int row, int col, int N) {
        return row >= 0 && row < N && col >= 0 && col < N;
    }

    double dfs(int N, int remaining_moves, int row, int col, Table& table) {
        if (table[row][col][remaining_moves] != -1.0) {
            return table[row][col][remaining_moves];
        }
        if (remaining_moves == 0) { return 1.0; }

        double valid_moves = 0.0;
        Moves next_squares = {{row-2,col-1}, {row-2,col+1}, {row+2,col-1}, {row+2,col+1},
                              {row-1,col-2}, {row-1,col+2}, {row+1,col-2}, {row+1,col+2}};
        for (const auto& square : next_squares) {
            if (is_valid(square.first, square.second, N)) {
                valid_moves += dfs(N, remaining_moves-1, square.first, square.second, table);
            }
        }
        table[row][col][remaining_moves] = valid_moves;
        return valid_moves;
    }

    double knightProbability(int N, int K, int row, int col) {
        Table table(N+1, std::vector<std::vector<double>>(N+1, std::vector<double>(K+1, -1.0)));
        double valid_moves = dfs(N, K, row, col, table);
        double total_moves = std::pow(8.0, K);
        return double(valid_moves) / total_moves;
    }
};

void test_knight_probability() {
    Solution soln;

    auto double_equals = [](double d1, double d2) { return std::fabs(d1 - d2) < 0.0001; };
    assert(double_equals(soln.knightProbability(8,30,6,4), 0.000190526));
    assert(double_equals(soln.knightProbability(3,2,0,0), 0.0625));
}

int main(int argc, char** argv) {
    test_knight_probability();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
