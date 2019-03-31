// Leetcode: https://leetcode.com/problems/sum-of-distances-in-tree/
// Given an undirected, connected tree with nodes labelled 0...N-1 and N-1 edges,
// Return an array A, where A[i] is the sum of the distances from node i to every
// other node in the tree

// Brute Force:
// Better:
// Acceptance: 38.2

#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>

struct Edge {
  int u = -1;           // From
  int v = -1;           // To
  bool operator==(const Edge& other) const { return u == other.u && v == other.v; }
};

struct EdgeData {
  int num_nodes = 0;   // # of discoverable nodes
  int distance = 0;    // Total distance of all discoverable nodes
  EdgeData& operator+=(const EdgeData ed) {
    num_nodes += ed.num_nodes;
    distance += ed.distance;
    return *this;
  }
};

struct EdgeHash {
  size_t operator()(const Edge& ew) const { return ew.u*13 + ew.v*17; }
};

using Graph = std::vector<std::vector<int>>;
using Cache = std::unordered_map<Edge, EdgeData, EdgeHash>;

// Accepted. 172ms. Faster than 42.09% of submissions.
class Solution {
public:
  EdgeData dfs(Graph& g, int parent, int vertex, Cache& cache) {
    EdgeData edge_data;
    const auto& neighbors = g[vertex];
    for (const auto& neighbor : neighbors) {
      if (neighbor != parent) {
        Edge e{vertex, neighbor};
        auto found = cache.find(e);
        if (found != cache.end()) {
          edge_data += found->second;
        } else {
          auto result = dfs(g, vertex, neighbor, cache);
          std::cout << "Edge from " << vertex << " to " << neighbor << " has weight " << result.distance << std::endl;
          cache[e] = result;
          edge_data += result;
        }
      }
    } // for
    edge_data.distance += (edge_data.num_nodes + 1);
    edge_data.num_nodes += 1;
    return edge_data;
  }

  std::vector<int> sumOfDistancesInTree(int N, std::vector<std::vector<int>>& edges) {
    Graph g(N, std::vector<int>());
    Cache cache;

    // Build a DAG - replace each undirected edge with two directed edges
    for (const auto& edge : edges) {
      g[edge[0]].emplace_back(edge[1]);
      g[edge[1]].emplace_back(edge[0]);
    }

    for (int v = 0; v < g.size(); ++v) {
      dfs(g, -1, v, cache);
    }

    std::vector<int> result(N, 0);
    for (int src = 0; src < g.size(); ++src) {
      for (const auto dest : g[src]) {
        Edge e{src, dest};
        // Lookup edge distance, every edge should be in the cache
        result[src] += cache[e].distance;
      }
    }
    return result;
  }
};

void test_sum_distances() {
  std::vector<std::vector<int>> undirected_edges{{0,1},{0,2},{2,3},{2,4},{2,5}};
  std::vector<int> expected{8,12,6,10,10,10};

  Solution soln;
  auto result = soln.sumOfDistancesInTree(6, undirected_edges);
  assert(result == expected);
}

int main(int argc, char** argv) {
  test_sum_distances();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
