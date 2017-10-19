// Leetcode: https://leetcode.com/problems/redundant-connection/description/
// Given a tree (undirected, acyclic graph) with nodes 1,2,...,N that has had a single edge added
// to it to form a cycle, return an edge that can be removed to restore the tree. If multiple
// such edges exist, return the one occurring last in the input edge list.

// Brute Force: 
// Better: Use DFS, tracking the path we explore.

#include <vector>
#include <iostream>
#include <unordered_set>
#include <assert.h>

using Edge = std::vector<int>;
using EdgeList = std::vector<Edge>;
using Neighbors = std::vector<int>;     // neighbors of a vertex
using Graph = std::vector<Neighbors>;   // Adjacency list

struct EdgeHash {
    size_t operator()(const Edge& e) const {
        return e[0] * 13 + e[1] * 19;
    }
};

using EdgeSet = std::unordered_set<Edge, EdgeHash>;

static const int NOT_VISITED = 0;
static const int IN_PROGRESS = 1;
static const int VISITED = 2;

// Accepted. 6ms. Beats 53% of submisssions, ties 45.08% of submissions.
class Solution {
public:
    // Return true if we found a cycle
    bool dfs_cycle(Graph& graph, int v, int parent, std::vector<int>& visited, EdgeList& path) {
        visited[v] = IN_PROGRESS;
        for (int i = 0; i < graph[v].size(); ++i) {
            auto neighbor = graph[v][i];
            if (neighbor == parent) { continue; }
            if (visited[neighbor] == NOT_VISITED) {
                auto from = std::min(v, neighbor);
                auto to = std::max(v, neighbor);
                path.emplace_back(Edge({from, to}));
                if (dfs_cycle(graph, neighbor, v, visited, path)) {
                    return true;
                }
                path.pop_back();
            } else if (visited[neighbor] == IN_PROGRESS) {
                // A cycle!
                EdgeList cycle;
                cycle.emplace_back(Edge({std::min(v,neighbor), std::max(v,neighbor)}));
                // Copy edges in the path until we get back to neighbor
                for (int i = path.size()-1; i >= 0; --i) {
                    cycle.emplace_back(path[i]);
                    if (path[i][0] == neighbor || path[i][1] == neighbor) { break; }
                }
                path = cycle;
                return true;
            }
        }
        visited[v] = VISITED;
        return false;
    }

    Edge findRedundantConnection(EdgeList& edges) {
        Graph graph(edges.size()+1, Neighbors()); // empty graph
        for (int i = 0; i < edges.size(); ++i) {
            auto u = edges[i][0];
            auto v = edges[i][1];
            graph[u].emplace_back(v);   // add edge u <--> v
            graph[v].emplace_back(u);   // add edge v <--> u
        }
        
        std::vector<int> visited(edges.size()+1, NOT_VISITED);
        EdgeList path;
        dfs_cycle(graph, edges[0][0], -1, visited, path); 

        EdgeSet edge_set;
        for (const auto& edge : path) {
            edge_set.emplace(edge);
        }

        for (int i = edges.size()-1; i >= 0; --i) {
            if (edge_set.count(edges[i])) {
                return edges[i];
            }
        }
        return Edge();
    }
};

bool test_redundant_connection(EdgeList edges, Edge should_remove) {
    Solution soln;
    auto redundant = soln.findRedundantConnection(edges);
    return redundant == should_remove;
}

void test_redundant_connection() {
    assert(test_redundant_connection({{1,2},{1,3},{2,3}}, {2,3}));
    assert(test_redundant_connection({{1,2},{2,3},{3,4},{1,4},{1,5}}, {1,4}));
    assert(test_redundant_connection({{30,44},{34,47},{22,32},{35,44},{26,36},{2,15},
                {38,41},{28,35},{24,37},{14,49},{44,45},{11,50},{20,39},{7,39},{19,22},
                {3,17},{15,25},{1,39},{26,40},{5,14},{6,23},{5,6},{31,48},{13,22},
                {41,44},{10,19},{12,41},{1,12},{3,14},{40,50},{19,37},{16,26},{7,25},
                {22,33},{21,27},{9,50},{24,42},{43,46},{21,47},{29,40},{31,34},{9,31},
                {14,31},{5,48},{3,18},{4,19},{8,17},{38,46},{35,37},{17,43}}, {5,48}));
}

int main(int argc, char** argv) {
    test_redundant_connection();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
