// Leetcode: https://leetcode.com/problems/cheapest-flights-within-k-stops/

// Brute Force: Calculate all possible paths, choose the optimal.
// Better: Modified Dijkstra's algorithm. However, instead of tracking a single cost for each vertex
// the heap holds any possible path to a city with less than k stops.

#include <set>
#include <vector>
#include <iostream>
#include <assert.h>

struct DirectedEdge {
  int dst = 0;
  int cost = 0;
};

struct Vertex {
  int v;
  std::vector<DirectedEdge> edges;
  Vertex(int vertex):v(vertex){}
};

struct City {
  int v;
  int cost = std::numeric_limits<int>::max();
  int stops = -1;
  City(int v, int c, int s): v(v), cost(c), stops(s) {}
};

struct CompareCities {
  bool operator()(const City& u, const City& v) {
    if (u.cost == v.cost) { 
      if (u.stops == v.stops) {
        return u.v < v.v;
      }
      return u.stops < v.stops;
    }
    return u.cost < v.cost;
  }
}; 

using Graph = std::vector<Vertex>;
using CitySet = std::set<City, CompareCities>;

// Accepted. 24ms. Faster than 25.88% of submissions.
class Solution {
public:
  int dijkstras(Graph& g, int src, int dst, int k) {
    CitySet heap; // not really a heap

    heap.emplace(City(g[src].v, 0, -1));
    while (!heap.empty()) {
      auto min_iter = heap.begin();  // lowest cost city 
      auto min = *min_iter;
      if (min.v == dst && min.stops <= k) { return min.cost; }
      heap.erase(min_iter);
      for (const auto edge : g[min.v].edges) {
        auto& dest = g[edge.dst];
        City city(dest.v, min.cost + edge.cost, min.stops + 1);
        if (city.stops <= k) {
          heap.insert(city);
        }
      } // for edge 
    }
    return -1;
  }

  int findCheapestPrice(int n, const std::vector<std::vector<int>>& flights, 
                        int src, int dst, int k) {
    Graph g;
    for (int i = 0; i < n; ++i) { g.emplace_back(Vertex(i)); }
    for (const auto flight : flights) {
      auto src = flight[0];
      auto dst = flight[1];
      auto cost = flight[2];
      g[src].edges.emplace_back(DirectedEdge{dst, cost});
    }
    return dijkstras(g, src, dst, k);
  }
};

bool test_costs(int n, const std::vector<std::vector<int>>& flights, 
    int src, int dst, int k, int expected) {
  Solution soln;
  auto price = soln.findCheapestPrice(n, flights, src, dst, k);
  return price == expected;
}

void test_costs() {
  assert(test_costs(4, {{0,1,100},{1,2,100},{0,2,500},{1,3,100},{2,3,100}}, 0, 3, 2, 200));
  assert(test_costs(4, {{0,1,1},{1,2,1},{0,2,5},{2,3,1}}, 0, 3, 1, 6));
  assert(test_costs(3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 1, 200));
  assert(test_costs(3, {{0,1,100},{1,2,100},{0,2,500}}, 0, 2, 0, 500));
}

int main(int argc, char** argv) {
  test_costs();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
