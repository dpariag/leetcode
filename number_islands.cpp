// Leetcode: https://leetcode.com/problems/number-of-islands/description/
// Given a grid of '1's and '0's, count the number of islands. An island is formed by connecting 
// adjacent 1's horizontally or vertically. Assume the entire grid is surrounded by water.

// Brute Force: Consider all subsets of adjacent squares.
// Better: Use depth-first-search from each square that is a '1'. Mark squares as visited to
// avoid visiting them more than once. O(n^2) since each square is visited once.

#include <vector>
#include <iostream>
#include <assert.h>

using Grid = std::vector<std::vector<char>>;

// Accepted. 6ms. Beats 27.59% of submissions, ties 68.77% of submissions.
class Solution {
public:

    inline void dfs(Grid& grid, int row, int col) {
        grid[row][col] = '0'; // visited 
        if (row > 0 && grid[row-1][col] == '1') {
            dfs(grid, row-1, col);
        }
        if (row < grid.size() - 1 && grid[row+1][col] == '1') {
            dfs(grid, row+1, col);
        }
        if (col > 0 && grid[row][col-1] == '1') {
            dfs(grid, row, col-1);
        }
        if (col < grid[0].size() -1 && grid[row][col+1] == '1') {
            dfs(grid, row, col+1);
        }
    }

    int numIslands(Grid& grid) {
        int num_islands = 0;
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (grid[row][col] == '1') {
                    ++num_islands;
                    dfs(grid, row, col);
                }
            }
        }
        return num_islands;
    }
};

bool test_number_islands(Grid grid, int expected_islands) {
    Solution soln;
    auto num_islands = soln.numIslands(grid);
    return num_islands == expected_islands;
}

void test_number_islands() {
    assert(test_number_islands({{'1','0','1','1'}, {'1','0','0','1'}, {'1','0','0','1'}}, 2));
    assert(test_number_islands({{'1','1','1','1'}, {'1','0','0','1'}, {'1','0','0','1'}}, 1));
    assert(test_number_islands({{'1','0','0','1'}, {'0','0','0','0'}, {'1','0','0','1'}}, 4));
    assert(test_number_islands({{'1','0','0','1'}, {'0','0','0','0'}, {'1','1','1','1'}}, 3));
    assert(test_number_islands({{'1','1','1','1'}, {'0','0','0','0'}, {'0','0','0','0'}}, 1));
}

int main(int argc, char** argv) {
    test_number_islands();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
