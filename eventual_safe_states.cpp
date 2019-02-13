// Leetcode: https://leetcode.com/problems/find-eventual-safe-states/
// In a directed graph, nodes with non outgoing edges are labeled 'safe'. Find all safe nodes as well nodes
// from which all nodes lead to safe nodes.

// Brute Force: For each node, examine all outgoing paths to see if any path leads to an unsafe node.
// Better: First pass labels safe nodes. Then use a modified DFS to explore the graph. Cycles indicate unsafe nodes.
// In the absence of a cycle, we must eventually end up at a safe node. O(V+E)
// Acceptance: 42.3

#include <iostream>
#include <vector>
#include <assert.h>

enum class State {
  SAFE = 0,
  UNSAFE = 1,
  UNKNOWN = 2
};

using Graph = std::vector<std::vector<int>>;
using States = std::vector<State>;

// Accepted. 180ms. Faster than 88.24% of cpp submissions.
class Solution {
public:
  std::vector<int> eventualSafeNodes(Graph& graph) {
    std::vector<bool> visited(graph.size(), false);
    States states(graph.size(), State::UNKNOWN);

    // Mark nodes with no neighbors as safe
    for (int i = 0; i < graph.size(); ++i) {
      if (graph[i].empty()) {
        states[i] = State::SAFE;
      }
    }
    
    std::vector<int> safe_nodes;
    for (int i = 0; i < graph.size(); ++i) {
      if (check_if_safe(graph, i, visited, states) == State::SAFE) {
        safe_nodes.emplace_back(i);
      }
    }
    return safe_nodes;
  }

  State check_if_safe(const Graph& graph, int v, std::vector<bool>& visited, States& states) {
    if (states[v] != State::UNKNOWN) { return states[v]; }
    if (visited[v]) { return State::UNSAFE; }

    visited[v] = true;
    State state = State::SAFE;
    const auto& neighbors = graph[v];
    for (const auto n : neighbors) {
      if (check_if_safe(graph, n, visited, states) == State::UNSAFE) {
        state = State::UNSAFE;
        break;
      } 
    }
    states[v] = state;
    return state;
  }
};

void test_eventual_safe_nodes() {
  Graph g({{1,2},{2,3},{5},{0},{5},{},{}});
  Solution soln;
  auto safe_nodes = soln.eventualSafeNodes(g);
  assert(safe_nodes == std::vector<int>({2,4,5,6}));
}

int main(int argc, char** argv) {
  test_eventual_safe_nodes();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
