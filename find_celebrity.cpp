// Leetcode: https://leetcode.com/problems/find-the-celebrity/description/

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

static const int c_unvisited = 0;
static const int c_in_progress = 1;
static const int c_visited = 2;

bool knows(int a, int b);

// Accepted. 976ms. Beats 2.02% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool knows_no_one(int cur, int n) {
        for (int i = 0; i < n; ++i) {
            if (i != cur && knows(cur, i)) { return false; }
        }
        return true;
    }

    void dfs(int cur, int n, std::vector<int>& incoming, std::vector<int>& visited) {
        incoming[cur]++;
        if (visited[cur] != c_unvisited) { return; }

        visited[cur] = c_in_progress;
        for (int i = 0; i < n; ++i) {
            if (i != cur && knows(cur, i)) {
                dfs(i, n, incoming, visited);
            }
        }
        visited[cur] = c_visited;
    }

    int findCelebrity(int n) {
        std::vector<int> incoming(n, 0);
        std::vector<int> visited(n, c_unvisited);

        for (int i = 0; i < n; ++i) {
            dfs(i, n, incoming, visited);
        }

        for (int i = 0; i < n; ++i) {
            if (incoming[i] == n && knows_no_one(i, n)) {
                return i;
            }
        }
        return -1;
    }
};


int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
