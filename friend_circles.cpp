// Leetcode: https://leetcode.com/problems/friend-circles/description/

// Brute Force:
// Better:

#include "debug.h"
#include <vector>
#include <iostream>
#include <assert.h>

using Matrix = std::vector<std::vector<int>>;

// Accepted. 28ms. Beats 5.96% of cpp submissions.
class Solution {
public:
    void dfs(Matrix& M, int i, int j) {
        M[i][j] = 0, M[j][i] = 0, M[i][i] = 0, M[j][j] = 0;
        for (j = 0; j < M[i].size(); ++j) {
            if (i != j && M[i][j] == 1) {
                dfs(M, j, i);
            }
        }
    }

    int findCircleNum(Matrix& M) {
        int num_circles = 0;
        for (int i = 0; i < M.size(); ++i) {
            bool circle = false;
            for (int j = 0; j < M[0].size(); ++j) {
                if (i != j && M[i][j] == 1) {
                    circle = true;
                    dfs(M, j, i);
                }
            }
            if (circle) ++num_circles;
        }
        for (int i = 0; i < M.size(); ++i) {
            if (M[i][i] == 1) ++num_circles;
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
