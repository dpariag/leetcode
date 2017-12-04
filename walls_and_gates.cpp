// Leetcode: https://leetcode.com/problems/walls-and-gates/description/
// Given a m x n 2D integer grid where values mean:
//  -1 : Wall/Obstacle, 0 : Gate, INF : Empty room, update each empty room with the distance
// to the nearest gate.

// Brute Force:
// Better:

#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

static const int INF = 2147483647;
static const int WALL = -1;
static const int ROOM = 0;
using Grid = std::vector<std::vector<int>>;

struct Cood {
    int row = 0;
    int col = 0;
    Cood(int r, int c): row(r), col(c) {}
    inline bool valid(const Grid& rooms) { return row >= 0 && row < rooms.size() && col >= 0 && col < rooms[0].size(); }
};

using Queue = std::queue<Cood>;

// Accepted. 92ms. Beats 93.81% of submissions, ties 4.01% of submissions.
class Solution {
public:
    void wallsAndGates(Grid& rooms) {        
        if (rooms.empty()) { return; }

        Queue q;
        // Initialize queue with all empty rooms
        for (int row = 0; row < int(rooms.size()); ++row) {
            for (int col = 0; col < rooms[0].size(); ++col) {
                if (rooms[row][col] == ROOM) {
                    q.emplace(row,col);
                }
            }
        }
        
        // BFS
        while (!q.empty()) {
            auto c = q.front();
            auto distance = rooms[c.row][c.col];

            //using Neighbors = std::vector<Cood>;
            Cood neighbors[4] = {Cood(c.row+1, c.col), Cood(c.row-1, c.col), Cood(c.row, c.col+1), Cood(c.row, c.col-1)};
            for (auto& n : neighbors) {
                if (n.valid(rooms) && rooms[n.row][n.col] > distance+1) {
                    // Update distance to a valid room with a shorter distance
                    rooms[n.row][n.col] = distance + 1;
                    q.emplace(n.row, n.col);
                }
            }
            q.pop();
        }

    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
