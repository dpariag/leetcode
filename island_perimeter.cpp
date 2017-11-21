// Leetcode: https://leetcode.com/problems/island-perimeter/description/
// You are given a matrix where '1' represents land and '0' represents water.
// The matrix contains one island. Find it's perimeter.

#include <vector>
#include <iostream>
#include <assert.h>

// Brute Force: Scan the matrix looking for '01', '10' combos in rows and columns. O(n^2) time.
// Better: Use DFS from one land cell to explore the entire island. Perimeter is calculated
// by tracking sides with no neighbors. O(n^2) runtime worst case, but better if the island is small.

using Visited = std::vector<std::vector<bool>>;
using Grid = std::vector<std::vector<int>>;

// Accepted. Beats 59.46% of submissions, ties 1.07% of submissions.
class Solution {
public:
    int dfs(Visited& visited, const Grid& grid, int row, int col) {
        int my_sides = 4;
        int perimeter = 0;
        visited[row][col] = true;

        using Neighbors = std::vector<std::pair<int, int>>;
        Neighbors neighbors({{row-1,col}, {row+1,col}, {row,col+1}, {row,col-1}});
        for (auto& n : neighbors) {
            if ((n.first >= 0 && n.first < grid.size()) && 
                (n.second >= 0 && n.second < grid[0].size())) {
                // Valid neighbor
                if (grid[n.first][n.second] == 1) {
                    // Neighbor is land, so that side can't contribute to perimeter
                    --my_sides;
                    if (!visited[n.first][n.second]) {
                        // Neighbor has not been visited, so visit now
                        perimeter += dfs(visited, grid, n.first, n.second);
                    }
                }
            }
        }
        return perimeter + my_sides;
    }

    int islandPerimeter(const Grid& grid) {
        if (grid.empty()) { return 0; }

        Visited visited(grid.size(), std::vector<bool>(grid[0].size(), false));
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (grid[row][col] == 1) {
                    return dfs(visited, grid, row, col);
                }
            }
        }
        return 0;
    }
};

void test_island_perimeter() {
    Solution soln;

    assert(soln.islandPerimeter({{0},{1}}) == 4);
    assert(soln.islandPerimeter({{0,1,0,0},{1,1,1,0},{0,1,0,0},{1,1,0,0}}) == 16);
}

int main(int argc, char** argv) {
    test_island_perimeter();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
