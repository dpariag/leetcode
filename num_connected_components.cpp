// Leetcode: https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/description/
// Given n nodes labeled from 0 to n - 1 and a list of undirected edges (a pair of nodes), 
// write a function to find the number of connected components in an undirected graph.

// Approach: Build a directed graph (each undirected edge turns into two edges), and conduct DFS from
// each unvisited vertex. Each DFS discovers a new component. O(V+E) time.

#include <vector>
#include <iostream>
#include <assert.h>

const int NOT_VISITED = 0;
const int VISITING = 1;
const int VISITED = 2;

using Graph = std::vector<std::vector<int>>;
using Visited = std::vector<int>;

// Accepted. 15ms. Beats 47.61% of submissions, ties 1.13% of submissions.
class Solution {
public:
    inline void dfs(const Graph& g, int vertex, Visited& visited) {
        visited[vertex] = VISITING;
        for (auto neighbor : g[vertex]) {
            if (visited[neighbor] == NOT_VISITED) {
                dfs(g, neighbor, visited);
            }
        }
        visited[vertex] = VISITED;
    }

    int countComponents(int n, std::vector<std::pair<int, int>>& edges) {
        Graph g(n);
        for (auto& e : edges) {
            g[e.first].emplace_back(e.second);
            g[e.second].emplace_back(e.first);
        }

        int components = 0;
        Visited visited(n, NOT_VISITED);
        for (int vertex = 0; vertex < n; ++vertex) {
            if (visited[vertex] == NOT_VISITED) {
                ++components;
                dfs(g, vertex, visited);                
            }
        }
        return components;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
