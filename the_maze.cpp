// Leetcode: https://leetcode.com/problems/the-maze/description/
// There is a ball in a maze with empty spaces and walls. The ball can roll up, down, left or right, 
// but it won't stop rolling until it hits a wall. When the ball stops, it can choose its next direction.
// Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination

// Approach: Use DP to calculate for each spot its 4 furthest neighbors (i.e., where the ball would stop).
// Then perform DFS from the ball's starting point to see if it can stop at the destination. O(N^2) time

#include <vector>
#include <iostream>
#include <assert.h>

struct Neighbor {
    int left = 0;   // col-index of leftmost neighbor
    int right = 0;  // col-index of rightmost neighbor
    int top = 0;    // row-index of top neighbor
    int bottom = 0; // row-index of bottom neighbor
};
using Neighbors = std::vector<std::vector<Neighbor>>;
using Maze = std::vector<std::vector<int>>;

// Accepted. 42ms. Beats 29.78% of submissions, ties 3% of submissions.
class Solution {
public:
    bool hasPath(Maze& maze, std::vector<int>& start, std::vector<int>& destination) {
        Neighbors neighbors(maze.size(), std::vector<Neighbor>(maze[0].size()));

        for (int row = 0; row < neighbors.size(); ++row) {
            for (int col = 0; col < neighbors[0].size(); ++col) {
                if (row > 0) {
                    neighbors[row][col].top = (maze[row-1][col] == 1) ? row : neighbors[row-1][col].top;
                }
                if (col > 0) {
                    neighbors[row][col].left = (maze[row][col-1] == 1) ? col : neighbors[row][col-1].left;
                }
            }
        }

        int num_rows = neighbors.size(), num_cols = neighbors[0].size();
        for (int row = num_rows - 1; row >= 0; --row) {
            for (int col = num_cols-1; col >= 0; --col) {
                neighbors[row][col].bottom = (row == num_rows-1 || maze[row+1][col] == 1) ? row : neighbors[row+1][col].bottom;
                neighbors[row][col].right  = (col == num_cols-1 || maze[row][col+1] == 1) ? col : neighbors[row][col+1].right;
            }
        }

        Maze visited(maze.size(), std::vector<int>(maze[0].size(), 0));
        return dfs(maze, neighbors, visited, start[0], start[1], destination[0], destination[1]);
    }

    bool dfs(const Maze& maze, Neighbors& neighbors, Maze& visited, int row, int col, int dest_row, int dest_col) {
        if (row == dest_row && col == dest_col) { return true; }

        visited[row][col] = 1;
        std::vector<std::pair<int,int>> to_visit = {{neighbors[row][col].top, col}, {neighbors[row][col].bottom, col}, 
                                                    {row, neighbors[row][col].left}, {row, neighbors[row][col].right}};
        for (auto n : to_visit) {
            int next_row = n.first, next_col = n.second;
            if (maze[next_row][next_col] != 1 && visited[next_row][next_col] != 1) {
                if (dfs(maze, neighbors, visited, next_row, next_col, dest_row, dest_col)) {
                    return true;
                }
            }
        }
        return false;
    }
};


int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
