// Leetcode: https://leetcode.com/problems/making-a-large-island/
// Given a grid of 0s and 1s, find the largest island that can be made by flipping one 0.

// Approach: Use DFS to discover all islands. For each 1 in the grid, record the island number that it belongs to.
// Separately record island sizes. A second pass scans for zeroes and checks how many islands can be connected
// by flipping that zero. Track the largest such island.
// Acceptance: 40.9

#include <iostream>
#include <set>
#include <vector>
#include <assert.h>
#include "debug.h"

using Grid = std::vector<std::vector<int>>;

// Accepted. 8ms. Faster than 97.51% of submissions.
class Solution {
public:
  int dfs(const Grid& grid, Grid& visited, int island_number, int i, int j) {
    int size = 1;
    visited[i][j] = island_number;
    std::vector<std::pair<int,int>> neighbors{{i+1,j}, {i-1,j},{i,j+1},{i,j-1}};
    for (const auto& n : neighbors) {
      if (n.first < grid.size() && n.second < grid.size()) {
        if (grid[n.first][n.second] == 1 && visited[n.first][n.second] == -1) {
          size += dfs(grid, visited, island_number, n.first, n.second);
        }
      }
    }
    return size;
  }

  int largestIsland(Grid& grid) {
    Grid visited(grid.size(), std::vector<int>(grid.size(), -1));
    std::vector<int> islands_sizes;
    int island_number = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid.size(); ++j) {
        if (grid[i][j] == 1 && visited[i][j] == -1) {
          int size = dfs(grid, visited, island_number++, i, j);
          islands_sizes.emplace_back(size);
        }
      }
    }

    int num_zeroes = 0;
    int largest = 0;
    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid.size(); ++j) {
        if (grid[i][j] == 0) {
          ++num_zeroes;
          std::set<int> neighbor_islands;
          std::vector<std::pair<int,int>> neighbors{{i+1,j}, {i-1,j},{i,j+1},{i,j-1}};
          for (auto n : neighbors) {
            if (n.first < grid.size() && n.second < grid.size()) {
              if (grid[n.first][n.second] == 1) {
                auto island = visited[n.first][n.second];
                neighbor_islands.emplace(island); 
              }
            }
          }
          int size = 0;
          for (const auto island : neighbor_islands) {
            size += islands_sizes[island];
          }
          largest = std::max(largest, size);
        }
      }
    }
    if (num_zeroes == 0) { return grid.size() * grid.size(); }
    return largest + 1;
  }
};

bool test_largest_island(Grid g, int expected) {
  Solution soln;
  return soln.largestIsland(g) == expected;
}

void test_largest_island() {
  assert(test_largest_island({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 1));
  assert(test_largest_island({{1,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,1}}, 2));
  assert(test_largest_island({{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, 2));
  assert(test_largest_island({{1,1,0,0},{0,0,0,1},{0,0,0,1},{1,1,0,0}}, 3));
  assert(test_largest_island({{1,1,1,1},{1,1,1,1},{1,1,0,1},{1,1,1,1}}, 16));
  assert(test_largest_island({{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}, 16));
  assert(test_largest_island({{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}}, 13));
  assert(test_largest_island({{0,1,1,0},{1,1,0,1},{0,1,0,1},{1,0,1,1}}, 11));
  assert(test_largest_island({{0,1,1,0},{1,1,1,1},{1,1,1,1},{0,1,1,0}}, 13));
}

int main(int argc, char** argv) {
  test_largest_island();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
