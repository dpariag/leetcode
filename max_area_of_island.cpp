// Leetcode: https://leetcode.com/problems/max-area-of-island/ 
// Given a grid of 0s and 1s, find the largest island of 1s, where cells are connected vertically
// or horizontally.

// Approach: Use DFS to explore unvisited cells. O(m*n) where the grid is m*n.

#include <vector>
#include <iostream>
#include <assert.h>

using Grid = std::vector<std::vector<int>>;

// Accepted. 12ms. Beats 99.30% of C++ submissions.
class Solution {
public:
  int dfs(Grid& grid, int row, int col) {
    if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() || grid[row][col] == 0) {
      return 0;
    }
    
    grid[row][col] = 0;           // Visit this cell
    return 1 + 
      dfs(grid, row-1, col) +     // Check above
      dfs(grid, row+1, col) +     // Check below
      dfs(grid, row, col-1) +     // Check left
      dfs(grid, row, col + 1);    // Check right
  }

  int maxAreaOfIsland(Grid& grid) {
    int max_area = 0;
    for (int row = 0; row < grid.size(); ++row) {
      for (int col = 0; col < grid[0].size(); ++col) {
        if (grid[row][col] == 1) {
          max_area = std::max(max_area, dfs(grid, row, col));
        }
      }
    }
    return max_area;
  }
};

bool test_max_area(Grid grid, int expected) {
  Solution soln;
  return soln.maxAreaOfIsland(grid) == expected;
}

void test_max_area() {
  assert(test_max_area({{0,0,0,1},{0,0,0,1},{0,0,1,1},{1,1,1,0}}, 7));
}

int main(int argc, char** argv) {
  test_max_area();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
