// Leetcode: https://leetcode.com/problems/friend-circles/description/
// Given a matrix M, where M[i][j] denotes that the i'th and j'th students are friends
// determine how many friend circles exist.

// Approach: Use DFS to scan the matrix. If i and j are friends, then continue DFS from j. O(n^2) time.
// This is an instance of finding connnected components in a graph, or the union-find algorithm.

#include "debug.h"
#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;
using Visited = std::vector<bool>;

// Accepted. 12ms. Beats 98.31% of cpp submissions.
class Solution {
public:
    void dfs(Matrix& M, int i, Visited& visited) {
        visited[i] = true;
        for (int j = 0; j < M[i].size(); ++j) {
            if (!visited[j] && i != j && M[i][j] == 1) {
                dfs(M, j, visited);
            }
        }
    }

    int findCircleNum(Matrix& M) {
        int num_circles = 0;
        Visited visited(M.size(), false);
        for (int i = 0; i < M.size(); ++i) {
            if (!visited[i]) {
                dfs(M, i, visited);
                ++num_circles;
            }
        }
        return num_circles;
    }
};

bool test_friend_circles(Matrix m, int expected_circles) {
    Solution soln;
    return soln.findCircleNum(m) == expected_circles;
}

void test_friend_circles() {
    assert(test_friend_circles({{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}}, 1));
    assert(test_friend_circles({{1,1,0},{1,1,0},{0,0,1}}, 2));
    assert(test_friend_circles({{1,1,0},{1,1,1},{0,1,1}}, 1));
    assert(test_friend_circles({ {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                                 {0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
                                 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                                 {0,1,0,1,0,0,0,1,0,0,0,1,0,0,0},
                                 {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
                                 {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                                 {0,0,0,1,0,0,0,1,1,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
                                 {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                                 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
                                 {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
                                 {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0},
                                 {0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
                                 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}, 8));
}

int main(int argc, char** argv) {
    test_friend_circles();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
