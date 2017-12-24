// Leetcode: https://leetcode.com/problems/bomb-enemy/description/
// Given a 2D grid where each cell is either a wall 'W', an enemy 'E' or empty '0', 
// return the maximum enemies you can kill by placing one bomb on an empty cell.
// The bomb kills all the enemies in the same row and column untless it hits a wall.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

struct Count {
    int above = 0;
    int below = 0;
    int left = 0;
    int right = 0;

    void set(int a, int b, int l, int r) {
        above = a, below = b, left = l, right = r;
    }

    int total() const { return above + below + left + right; }
};
using Grid = std::vector<std::vector<char>>;
using Counts = std::vector<std::vector<Count>>;

// Accepted. 36ms. Beats 33.94% of submissions, ties 21.52% of submissions.
class Solution {
public:
    int maxKilledEnemies(const Grid& grid) {
        if (grid.empty() || grid[0].empty()) { return 0; }
        int num_rows = grid.size(), num_cols = grid[0].size();
        Counts counts(num_rows, std::vector<Count>(num_cols));

        for (int row = int(num_rows-1); row >= 0; --row) {
            for (int col = int(num_cols-1); col >= 0; --col) {
                switch (grid[row][col]) {
                    case 'E':
                        counts[row][col].set(1,1,1,1);
                        // fall through
                    case '0':
                        counts[row][col].right += (col < num_cols-1) ? counts[row][col+1].right : 0;
                        counts[row][col].below += (row < num_rows-1) ? counts[row+1][col].below : 0;
                        break;
                }
            }
        }

        int max_enemies = 0;
        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                switch (grid[row][col]) {
                    case 'E':
                    case '0':
                        counts[row][col].left += (col > 0) ? counts[row][col-1].left : 0;
                        counts[row][col].above += (row > 0) ? counts[row-1][col].above : 0;
                }
                if (grid[row][col] == '0') {
                    max_enemies = std::max(max_enemies, counts[row][col].total());    
                }
                
            }
        }
        return max_enemies;
    }
};

void test_max_enemies() {
    Solution soln;
    assert(soln.maxKilledEnemies({{'W','E','E','E','E','0','E','E','E','E','E','W'}}) == 9);
    assert(soln.maxKilledEnemies({{'E'}}) == 0);
    assert(soln.maxKilledEnemies({{'0','E','0','0'}, {'E','0','W','E'}, {'0','E','0','0'}}) == 3);
}

int main(int argc, char** argv) {
    test_max_enemies();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
