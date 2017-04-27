// Leetcode: https://leetcode.com/problems/brick-wall/#/description
// See URL for the rather involved description

// Brute Force:
// Better: Iterate each row of the wall, calculating a running row sum. Count the number of
// occurences of unique row sums. Row sums that occur more than once represent edge-aligned bricks.
// O(n^2) time and O(n) space.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

const int max_cols = 10000;

// Accepted. 42ms. Beats 67.01% of submissions, ties 18.24% of submissions.
class Solution {
public:
    int leastBricks(std::vector<std::vector<int>>& wall) {
        std::vector<int> row_sums(wall.size(), 0);
        std::unordered_map<int,int> sum_counts;
        bool done = false;
        int max_sum_count = 0;

        for (int col = 0; col < max_cols && !done; ++col) {
            done = true;
            for (int row = 0; row < wall.size(); ++row) {
                if (col < wall[row].size() - 1) {
                    done = false;
                    row_sums[row] += wall[row][col];
                    int sum_count = ++sum_counts[row_sums[row]];
                    max_sum_count = std::max(max_sum_count, sum_count);
                } 
            }
        }
        return wall.size() - max_sum_count;
    }
};

bool test_least_bricks(std::vector<std::vector<int>> wall, int expected_least) {
    Solution soln;
    return soln.leastBricks(wall) == expected_least;
}

void test_least_bricks() {
    assert(test_least_bricks({{1}},1));
    assert(test_least_bricks({{1,5},{5,1}},1));
    assert(test_least_bricks({{1,1,2,2},{3,1,2}, {1,3,2},{2,4},{3,1,2},{1,3,1,1}},1));
    assert(test_least_bricks({{1,2,2,1},{3,1,2}, {1,3,2},{2,4},{3,1,2},{1,3,1,1}},2));
}

int main(int argc, char** argv) {
    test_least_bricks();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
