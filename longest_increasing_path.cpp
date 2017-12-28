// Leetcode: https://leetcode.com/problems/longest-increasing-path-in-a-m/description/
// Given an integer m, find the length of the longest increasing path.

// Brute Force: Peform depth-first-search from each matrix[i][j]. O(n^4) time.
// Better: Store paths[i][j] = {The longest path starting at matrix[i][j]} and use this to memoize the DFS.
// Improves runtime to O(n^2) since each square is visited at most once. 

#include <vector>
#include <iostream>
#include <assert.h>

struct Cood {
    int row = 0;
    int col = 0;
};

using Matrix = std::vector<std::vector<int>>;
static const int NOT_VISITED = -1;

// Accepted. 36ms. Beats 57.49% of submissions, ties 14.12% of submissions.
class Solution {
public:
    inline bool is_valid(const Cood& c, int num_rows, int num_cols) {
        return c.row >= 0 && c.row < num_rows && c.col >= 0 && c.col < num_cols;
    }

    int dfs(const Matrix& m, Matrix& paths, int row, int col) {
        if (paths[row][col] != NOT_VISITED) { return paths[row][col]; }
         
        int longest = 1;
        using Coods = std::vector<Cood>;
        Coods neighbors{{row-1,col},{row+1,col},{row,col-1},{row,col+1}};
        for (auto n : neighbors) {
            if (is_valid(n, m.size(), m[0].size()) && m[row][col] < m[n.row][n.col]) {
                // Valid neighbor with a larger value
                dfs(m, paths, n.row, n.col);
                longest = std::max(longest, 1+paths[n.row][n.col]);
            }
        }
        paths[row][col] = longest;
        return longest;
    }

    int longestIncreasingPath(Matrix& m) {
        if (m.empty()) { return 0; }
        
        int longest = 0, num_rows = m.size(), num_cols = m[0].size();
        Matrix paths(m.size(), std::vector<int>(m[0].size(), NOT_VISITED));

        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                longest = std::max(longest, dfs(m, paths, row, col));
            }
        }
        return longest;
    }
};

bool test_longest_path(Matrix m, int expected) {
    Solution soln;
    return soln.longestIncreasingPath(m) == expected;
}

void test_longest_path() {
    assert(test_longest_path({{3,4,5},{3,2,6},{2,2,1}}, 4));
    assert(test_longest_path({{9,9,4},{6,6,8},{2,1,1}}, 4));
    assert(test_longest_path({{3,8,5},{4,7,6},{5,6,1}}, 6));
    assert(test_longest_path({{1,2,3},{8,9,4},{7,6,5}}, 9));
}

int main(int argc, char** argv) {
    test_longest_path();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
