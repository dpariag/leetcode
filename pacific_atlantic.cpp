// Leetcode: https://leetcode.com/problems/pacific-atlantic-water-flow/description/
// Given an matrix of non-negative integers representing heights of a continent, the Pacific ocean 
// touches the left/top edges and the Atlantic ocean touches the right/bottom edges. Water flows 
// up/down/left/right to a cell of equal or lower height. Return all grid cood where water can flow 
// to both the Pacific and Atlantic ocean.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;
using Reachable = std::vector<std::vector<int>>;
using Coods = std::vector<std::pair<int, int>>;

static const int cPacific = 1;
static const int cAtlantic = 2;
static const int cBoth = 3;
static const int cVisited = 4;

// Accepted. 222ms. Beats 6.08% of submissions, ties < 1% of submissions.
class Solution {
public:
    inline bool valid_row(const Matrix& m, int row) { return row >= 0 && row < m.size(); }
    inline bool valid_col(const Matrix& m, int col) { return col >= 0 && col < m[0].size(); }

    int dfs(const Matrix& m, Reachable& r, int row, int col, char target) {
        if (row < 0 || row >= m.size() || col < 0 || col >= m[0].size()) { return 0; }        
        if (r[row][col] & cVisited) { return r[row][col]; }
        if ((r[row][col] & target) == target) { return target; }
        
        r[row][col] |= cVisited; // mark visited
        using Cells = std::vector<std::pair<int,int>>;
        for (auto& cell : Cells({{row-1,col}, {row,col-1}, {row+1, col}, {row, col+1}})) {
            int next_row = cell.first, next_col = cell.second;
            if (valid_row(m, next_row) && valid_col(m, next_col) &&
                m[next_row][next_col] <= m[row][col]) {
                r[row][col] |= dfs(m, r, next_row, next_col, target);
                if ((r[row][col] & target) == target) {
                    r[row][col] ^= cVisited; // unvisit
                    return r[row][col];
                }
            }
        }
        r[row][col] ^= cVisited; // unvisit
        return r[row][col];
    }

    Coods pacificAtlantic(const Matrix& m) {
        if (m.empty()) { return Coods(); }

        Reachable reachable(m.size(), std::vector<int>(m[0].size(), 0));
        for (int row = 0; row < m.size(); ++row) {
            reachable[row].front() |= cPacific;
            reachable[row].back()  |= cAtlantic;
        }

        for (int col = 0; col < m[0].size(); ++col) {
            reachable.front()[col] |= cPacific;
			reachable.back()[col]  |= cAtlantic;
        }

        for (int row = 0; row < m.size(); ++row) {
            for (int col = 0; col < m[0].size(); ++col) {
                dfs(m, reachable, row, col, cBoth);
            }
        }
       
        Coods result; 
        for (int row = 0; row < m.size(); ++row) {
            for (int col = 0; col < m[0].size(); ++col) {
                if ((reachable[row][col] & cAtlantic) &&
                    (reachable[row][col] & cPacific)) {
                    result.emplace_back(std::make_pair(row, col));
                }
            }
        }
        return result;
    }
};

bool test_pacific_atlantic(const Matrix& m, const Coods cood) {
    Solution soln;
    auto result = soln.pacificAtlantic(m);
    return result == cood;
}

void test_pacific_atlantic() {
    assert(test_pacific_atlantic({{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5}, {5,1,1,2,4}}, 
                {{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0}}));

    assert(test_pacific_atlantic({{1,2,3,4},{12,13,14,5},{11,16,15,6},{10,9,8,7}}, 
                {{0,3},
                 {1,0},{1,1},{1,2},{1,3},
                 {2,0},{2,1},{2,2},{2,3},
                 {3,0},{3,1},{3,2},{3,3}}));

}

int main(int argc, char** argv) {
    test_pacific_atlantic();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
