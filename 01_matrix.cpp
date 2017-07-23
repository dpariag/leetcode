// Leetcode: https://leetcode.com/problems/01-matrix/#/description
// Given a matrix of 0s and 1s with at least one 0, find the distance from each cell to a nearest 0.

// Brute Force: BFS from each cell until a zero cell is discovered. O(n^4) time.
// Better:

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;
using Visited = std::vector<std::vector<bool>>;

struct Index {
    int row = 0;
    int col = 0;
    int distance = 0;
    Index(int r, int c, int d): row(r), col(c), distance(d) {}
};

// Accepted. 203ms. Beats 97.25% of cpp submissions, ties ~1.5% of submissions.
class Solution {
public:
    Matrix updateMatrix(Matrix& matrix) {
        Visited visited(matrix.size(), std::vector<bool>(matrix[0].size(),false));
        std::queue<Index> to_visit;

        // Start exploring from zero-cells
        for (int row = 0; row < matrix.size(); ++row) {
            for (int col = 0; col < matrix[0].size(); ++col) {
                if (matrix[row][col] == 0) {
                    to_visit.emplace(Index(row, col, 0));
                    visited[row][col] = true;
                }
            }
        }

        while (!to_visit.empty()) {
            int row = to_visit.front().row;
            int col = to_visit.front().col;
            int distance = to_visit.front().distance;
            visited[row][col] = true;
            matrix[row][col] = distance;
            to_visit.pop();

            if (row-1 >= 0 && !visited[row-1][col]) {
                visited[row-1][col] = true;
                to_visit.emplace(Index(row-1, col, distance+1));
            }
            if (row+1 < matrix.size() && !visited[row+1][col]) {
                visited[row+1][col] = true;
                to_visit.emplace(Index(row+1, col, distance+1));
            }
            if (col-1 >= 0 && !visited[row][col-1]) {
                visited[row][col-1] = true;
                to_visit.emplace(Index(row, col-1, distance+1));
            }
            if (col+1 < matrix[0].size() && !visited[row][col+1]) {
                visited[row][col+1] = true;
                to_visit.emplace(Index(row, col+1, distance+1));
            }
        }
        return matrix;
    }
};

bool test_01_matrix(Matrix m, Matrix expected) {
    Solution soln;
    auto updated = soln.updateMatrix(m);
    return updated == expected;
}

void test_01_matrix() {
    test_01_matrix({{0,0,0},{0,1,0},{0,0,0}}, {{1,0,1},{0,1,0},{1,2,1}});
    test_01_matrix({{1,0,1},{0,1,0},{1,1,1}}, {{1,0,1},{0,1,0},{1,2,1}});
    test_01_matrix({{1,1,1},{0,1,0},{1,1,1}}, {{1,2,1},{0,1,0},{1,2,1}});
    test_01_matrix({{1,1,1},{1,1,1},{1,1,0}}, {{4,3,2},{3,2,1},{2,1,1}});
}

int main(int argc, char** argv) {
    test_01_matrix();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
