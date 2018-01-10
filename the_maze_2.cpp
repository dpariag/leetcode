// Leetcode: https://leetcode.com/problems/the-maze/description/

// Approach: We need to calculate the shortest path between two points in a graph.
// We use Dijkstra's algorithm using a priority queue to extract the next shortest
// path from the current vertex, and using a 2D-array to store shortest path so far to (row,col)
// O(N^2 * logN) time and space.

#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <assert.h>

struct Neighbor {
    int left = 0;   // col-index of leftmost neighbor
    int right = 0;  // col-index of rightmost neighbor
    int top = 0;    // row-index of top neighbor
    int bottom = 0; // row-index of bottom neighbor
    
    int top_dist = 0;
    int bottom_dist = 0;
    int left_dist = 0;
    int right_dist = 0;
};
using Neighbors = std::vector<std::vector<Neighbor>>;
using Maze = std::vector<std::vector<int>>;

struct Cood {
    int row = -1;
    int col = -1;
    int distance = 0;
    Cood(int r, int c, int d): row(r), col(c), distance(d) {}
    bool operator>(const Cood& other) const { return distance > other.distance; }
};
using Queue = std::priority_queue<Cood, std::vector<Cood>, std::greater<Cood>>;

// Accepted. 59ms. Beats 23.81% of submissions, ties 0.68% of submissions.
class Solution {
public:
    int shortestDistance(Maze& maze, const std::vector<int>& start, const std::vector<int>& destination) {
        Neighbors neighbors(maze.size(), std::vector<Neighbor>(maze[0].size()));

        for (int row = 0; row < neighbors.size(); ++row) {
            for (int col = 0; col < neighbors[0].size(); ++col) {
                if (row > 0) {
                    neighbors[row][col].top = (maze[row-1][col] == 1) ? row : neighbors[row-1][col].top;
                    neighbors[row][col].top_dist = (maze[row-1][col] == 1) ? 0 : neighbors[row-1][col].top_dist + 1;
                }
                if (col > 0) {
                    neighbors[row][col].left = (maze[row][col-1] == 1) ? col : neighbors[row][col-1].left;
                    neighbors[row][col].left_dist = (maze[row][col-1] == 1) ? 0 : neighbors[row][col-1].left_dist + 1;
                }
            }
        }

        int num_rows = neighbors.size(), num_cols = neighbors[0].size();
        for (int row = num_rows - 1; row >= 0; --row) {
            for (int col = num_cols-1; col >= 0; --col) {
                neighbors[row][col].bottom = (row == num_rows-1 || maze[row+1][col] == 1) ? row : neighbors[row+1][col].bottom;
                neighbors[row][col].bottom_dist = (row == num_rows-1 || maze[row+1][col] == 1) ? 0 : neighbors[row+1][col].bottom_dist + 1;

                neighbors[row][col].right  = (col == num_cols-1 || maze[row][col+1] == 1) ? col : neighbors[row][col+1].right;
                neighbors[row][col].right_dist  = (col == num_cols-1 || maze[row][col+1] == 1) ? 0 : neighbors[row][col+1].right_dist + 1;
            }
        }
        return dijkstra(maze, neighbors, start[0], start[1], destination[0], destination[1]);
    }

    int dijkstra(const Maze& maze, Neighbors& neighbors, int row, int col, int dest_row, int dest_col) {
        Maze distances(maze.size(), std::vector<int>(maze[0].size(), std::numeric_limits<int>::max()));
        Queue q;

        q.emplace(row, col, 0);
        while (!q.empty()) {
            auto c = q.top();
            q.pop();

            distances[c.row][c.col] = std::min(distances[c.row][c.col], c.distance);

            // Triples (row,col,distance). Order is top, bottom, left, right
            auto& neighbor = neighbors[c.row][c.col];
            std::vector<std::vector<int>> to_visit = {{neighbor.top, c.col, neighbor.top_dist}, {neighbor.bottom, c.col, neighbor.bottom_dist},
                                                      {c.row, neighbor.left, neighbor.left_dist}, {c.row, neighbor.right, neighbor.right_dist}};
            for (auto n : to_visit) {
                int next_row = n[0], next_col = n[1], distance = n[2];
                if (maze[next_row][next_col] != 1 && c.distance + distance < distances[next_row][next_col]) {
                    q.emplace(next_row, next_col, c.distance + distance);
                }
            }
        }
        return (distances[dest_row][dest_col] == std::numeric_limits<int>::max() ? -1 : distances[dest_row][dest_col]);
    }
};

void test_shortest_distance() {
    Solution soln;
    Maze m{{0,0,1,0,0},{0,0,0,0,0},{0,0,0,1,0},{1,1,0,1,1},{0,0,0,0,0}};
    assert(soln.shortestDistance(m, {0,4}, {4,4}) == 12);
}

int main(int argc, char** argv) {
    test_shortest_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}