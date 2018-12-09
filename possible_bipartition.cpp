// Leetcode: https://leetcode.com/problems/possible-bipartition/

// Brute Force: Generate all possible sets of people, then check each set for violations.
// Better: Build a graph (undirected edges) representing dislikes among people.
// Determine if the graph can be 2-colored using DFS. O(V+E) time
// Acceptance: 39.2

#include <iostream>
#include <vector>
#include <assert.h>

enum class Color {Black, White, None};
using Colors = std::vector<Color>;
using Graph = std::vector<std::vector<int>>; // Adjacency list

// Accepted. 80ms. Faster than 99.06% of submissions.
class Solution {
public:
  bool colored_dfs(const Graph& dislike_graph, Colors& colors, int v, Color cur_color, Color next_color) {
    colors[v] = cur_color; // visit
    const auto& dislikes = dislike_graph[v];
    for (const auto dislike : dislikes) {
      if (colors[dislike] == cur_color) { 
        return false; 
      } else if (colors[dislike] == next_color) {
        // OK, do nothing
      } else {
        if (!colored_dfs(dislike_graph, colors, dislike, next_color, cur_color)) {
          return false;
        } 
      }
    }
    return true;
  }

  bool possibleBipartition(int N, std::vector<std::vector<int>>& dislikes) {
    Colors colors(N+1, Color::None);
    Graph graph(N+1, std::vector<int>());
    
    for (const auto& dislike : dislikes) {
      graph[dislike.front()].emplace_back(dislike.back()); 
      graph[dislike.back()].emplace_back(dislike.front()); 
    }

    for (int i = 1; i <= N; ++i) {
      if (colors[i] == Color::None) {
        if (!colored_dfs(graph, colors, i, Color::Black, Color::White)) {
          return false;
        }
      }
    }
    return true;
  }
};

bool test_possible_bipartition(std::vector<std::vector<int>> dislikes, int N, bool expected) {
  Solution soln;
  return soln.possibleBipartition(N, dislikes) == expected;
}

void test_possible_bipartition() {
  assert(test_possible_bipartition({{1,2},{1,3},{2,3}}, 3, false));
  assert(test_possible_bipartition({{1,2},{1,3},{2,4}}, 4, true));
}

int main(int argc, char** argv) {
  test_possible_bipartition();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
