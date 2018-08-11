// Leetcode: https://leetcode.com/problems/is-graph-bipartite/description/
// Given an undirected graph, return true if and only if it is bipartite.

// Approach: Perform BFS from every unvisited node, assigning a colour to each node.

#include <iostream>
#include <queue>
#include <vector>
#include <assert.h>

constexpr int NO_SET = 0;
constexpr int SET_A  = 1;
constexpr int SET_B  = 2;

using Graph = std::vector<std::vector<int>>;
using Partition = std::vector<int>;
using Queue = std::queue<int>;

// Accepted. 12ms. Beats 99.23% of submissions.
class Solution {
public:
    bool bfs_bipartite(Graph& g, Partition& partition, int start_vertex) {
        Queue q;
        q.emplace(start_vertex); 
        partition[start_vertex] = SET_A;

        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            auto target_set = (partition[v] == SET_A) ? SET_B : SET_A;
            for (auto neighbor : g[v]) {
                if (partition[neighbor] == NO_SET) {
                    partition[neighbor] = target_set;
                    q.emplace(neighbor);
                } else if (partition[neighbor] != target_set) {
                    return false;
                }
            }
        }
        return true;
    }
 
    bool isBipartite(Graph& graph) {
        Partition partition(graph.size(), NO_SET);
        for (int v = 0; v < graph.size(); ++v) {
            if (partition[v] == NO_SET) {
                if (bfs_bipartite(graph, partition, v) == false) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
