// Leetcode: https://leetcode.com/problems/shortest-distance-from-all-buildings/description/
// Given a 2D grid with the following values: 0 : empty land, 1 : building, 2 : obstacle
// Find the empty land which reaches all buildings in the shortest manhattan distance.

// Brute Force:
// Better:

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

static const int BUILDING = -1;
static const int OBSTACLE = -2;

struct Cood {
    int row;
    int col;
    int distance;
    Cood(int r, int c, int d): row(r), col(c), distance(d) {}
};

using Grid = std::vector<std::vector<int>>;
using Queue = std::queue<Cood>;

// Accepted. 43ms. Beats 43.27% of submissions, ties 1.82% of submissions.
class Solution {
public:

    void bfs(Grid& grid, Grid& visited, Grid& reachable, int row, int col) {
        Queue q;

        q.emplace(row, col, 0);
        visited[row][col] = 1;

        while (!q.empty()) {
            auto cood = q.front();
            auto distance = cood.distance;
            std::pair<int,int> neighbors[4] = {{cood.row+1, cood.col}, {cood.row-1, cood.col}, 
                                               {cood.row, cood.col+1}, {cood.row, cood.col-1}};
            for (auto& n : neighbors) {
                if (n.first >= 0 && n.first < grid.size() && 
                    n.second >= 0 && n.second < grid[0].size()) {
                    auto& cur = grid[n.first][n.second];
                    if (cur != BUILDING && cur != OBSTACLE && visited[n.first][n.second] == 0) {
                        grid[n.first][n.second] += (distance + 1);
                        visited[n.first][n.second] = 1;
                        q.emplace(n.first, n.second, distance+1);
                        reachable[n.first][n.second]++;
                    }
                }
            }
            q.pop();
        }
    }

    int shortestDistance(Grid& grid) {
        int min_distance = -1, num_buildings = 0;

        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (grid[row][col] == 1) { ++num_buildings; }
                grid[row][col] *= -1;
            }
        }

        Grid reachable(grid.size(), std::vector<int>(grid[0].size(), 0));
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (grid[row][col] == BUILDING) {
                    Grid visited(grid.size(), std::vector<int>(grid[0].size(), 0));
                    bfs(grid, visited, reachable, row, col);
                }
            }
        }

        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (reachable[row][col] == num_buildings) {
                    if (min_distance < 0 || grid[row][col] < min_distance) { 
                        min_distance = grid[row][col]; 
                    }
                }
            }
        }
        return min_distance;
    }
};

bool test_shortest_distance(Grid grid, int expected) {
    Solution soln;
    return soln.shortestDistance(grid) == expected;
}

void test_shortest_distance() {
    assert(test_shortest_distance({{1,0,2,0,1},{0,0,0,0,0},{0,0,1,0,0}}, 7));
}

int main(int argc, char** argv) {
    test_shortest_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
