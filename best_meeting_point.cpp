// Leetcode: https://leetcode.com/problems/best-meeting-point/description/
// Given a grid where 1 represents a home, and zero an arbitrary venue, find the best meeting
// spot (home/venue) assuming each person must travel (Manhattan distance) from their home.

// Brute Force: For each square, calculate the Manhattan distance to every point. O(n^4)
// Better: Count houses in each row and col, and calculate the Manhattan distance to (0,0) from each.
// Compute first column Manhattan distances based on (0,0)
// Then sweep grid calculating Manhattan distances based on left neighbor's Manhattan distance.

#include <vector>
#include <iostream>
#include <assert.h>

using Grid = std::vector<std::vector<int>>;

// Accepted. 6ms. Beats 25.64% of submissions, ties 54.49% of submissions.
class Solution {
public:
    int minTotalDistance(const Grid& grid) {
        if (grid.empty()) { return 0; }

        std::vector<int> row_counts(grid.size(), 0);
        std::vector<int> col_counts(grid[0].size(), 0);

        int distance = 0, num_houses = 0;
        for (int row = 0; row < grid.size(); ++row) {
            for (int col = 0; col < grid[0].size(); ++col) {
                if (grid[row][col] == 1) { 
                    ++num_houses;
                    ++row_counts[row], ++col_counts[col];
                    distance += (row + col); // distance to (0,0)
                }
            }
        }

        Grid distances(grid.size(), std::vector<int>(grid[0].size(), 0));
        distances[0][0] = distance;
        int min_distance = distance;
        int num_above = 0;
        // We know total distance to (0,0), now fill in the first column.
        for (int row = 1; row < grid.size(); ++row) {
            num_above += row_counts[row-1];
            // Houses above (row,0) have to move to (row-1,0) then one more spot
            // Houses below (row,0) have to move to one less spot compared to (row-1,0)
            distances[row][0] = distances[row-1][0] + num_above - (num_houses - num_above);
            min_distance = std::min(min_distance, distances[row][0]);
        }


        for (int row = 0; row < grid.size(); ++row) {
            int num_left =  0;
            for (int col = 1; col < grid[0].size(); ++col) {
                num_left += col_counts[col-1];
                // Houses to the left have to move to (row,col-1) plus one more spot
                // Houses to the right have to move one less spot compared to (row,col-1)
                distances[row][col] = distances[row][col-1] + num_left - (num_houses - num_left);
                min_distance = std::min(min_distance, distances[row][col]);
            }
        }
        return min_distance;
    }
};

void test_min_distance() {
    Solution soln;

    assert(soln.minTotalDistance({{1},{1}}) == 1);
    assert(soln.minTotalDistance({{1,0,0,0,1}, {0,0,0,0,0},{0,0,1,0,0}}) == 6);
}

int main(int argc, char** argv) {
    test_min_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
