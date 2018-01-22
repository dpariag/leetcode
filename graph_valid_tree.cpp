// Leetcode: https://leetcode.com/problems/graph-valid-tree/description/
// Given nodes 0 to n - 1 and a list of undirected edges (node pairs), determine if the 
// graph is a valid tree.

// Approach: Build an adjacency list from undirected edges. DFS from first vertex,
// visiting each neighbor except the parent. Use 3 colors in DFS to detect cycles.
// The graph is a tree iff it is connected and acyclic.

#include <vector>
#include <iostream>
#include <assert.h>

using Edge = std::pair<int,int>;
using Edges = std::vector<Edge>;
using Graph = std::vector<std::vector<int>>;
using Visited = std::vector<int>;

static const int UNVISITED = 0;
static const int VISITING = 1;
static const int VISITED = 2;

// Accepted. 13ms. Beats 26.38% of submissions, ties 14.53% of submissions.
class Solution {
public:
    bool dfs(const Graph& graph, Visited& visited, int vertex, int parent) {
        visited[vertex] = VISITING;
        
        for (auto neighbor : graph[vertex]) {
            if (neighbor == parent) { continue; }
        
            if (visited[neighbor] == UNVISITED) {    
                if (dfs(graph, visited, neighbor, vertex) == false) { return false; }
            } else if (visited[neighbor] == VISITING) {
                return false;
            }
        }
        visited[vertex] = VISITED;
        return true;
    }


    bool validTree(int n, Edges& edges) {
        if (n == 0) { return true; }

        Visited visited(n, UNVISITED);
        Graph graph(n);

        for (auto& e : edges) {
            graph[e.first].emplace_back(e.second);
            graph[e.second].emplace_back(e.first);
        }

        if (!dfs(graph, visited, 0, -1)) { return false; }  // No cycles
        for (auto v : visited) { if (!v) return false; }    // Every vertex visited
        return true;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}