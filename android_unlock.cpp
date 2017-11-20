// Leetcode: https://leetcode.com/problems/android-unlock-patterns/description/
// Given a 3x3 key Android lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the 
// total number of unlock patterns of the Android lock screen, which consist of at least m keys 
// and at most n keys.

// Based on a submission in the leetcode discussion.
// Approach: DFS from each square. Neighbors of a square are either adjacent,
// or are neighbors of an already visited square.

#include <vector>
#include <iostream>
#include <assert.h>

using Visited = std::vector<int>;
using Grid = std::vector<std::vector<int>>;

// Accepted. 29ms. Beats 44.93% of submissions, ties 10%
class Solution {
public:
    int dfs(Visited& visited, Grid& skip, int cur, int len) {
        if (len <= 1) { return len; }
        
        visited[cur] = 1;
        int ways = 0;
        for (int next = 1; next <= 9; ++next) {
            // Next square can't be visited, and it must either be adjacent (skip = 0), 
            // or the square it skips over is visited
            if (!visited[next] && (skip[cur][next] == 0 || visited[skip[cur][next]])) {
                ways += dfs(visited, skip, next, len-1);
            }
        }
        visited[cur] = 0;
        return ways;
    } 

    int numberOfPatterns(int m, int n) {
        Visited visited(10, 0);
        Grid skip(10, std::vector<int>(10, 0));
        
        skip[1][3] = skip[3][1] = 2;
        skip[1][7] = skip[7][1] = 4;
        skip[3][9] = skip[9][3] = 6;
        skip[7][9] = skip[9][7] = 8;
        skip[1][9] = skip[9][1] = skip[2][8] = skip[8][2] = skip[4][6] = skip[6][4] = 5;
        skip[3][7] = skip[7][3] = 5;

        int ways = 0;
        for (int len = m; len <= n; ++len) {
            for (int cur = 1; cur <= 9; ++cur) {
                ways += dfs(visited, skip, cur, len);
            }
        }
        return ways;
    }
};

void test_num_patterns() {
    Solution soln;

    assert(soln.numberOfPatterns(1,1) == 9);
    assert(soln.numberOfPatterns(1,2) == 65);
    assert(soln.numberOfPatterns(1,3) == 385);
}

int main(int argc, char** argv) {
    test_num_patterns();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
