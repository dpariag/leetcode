// Leetcode: https://leetcode.com/problems/alien-dictionary/description/

// Approach: Build a graph whose vertices are letters, and whose edges indicate ordering 
// (i.e., 'a' comes before 'b') in the alien alphabet. Use the lexicographical ordering of
// words to find edges. Once built, perform a topological sort on the graph to determine
// a possible ordering of the alphabet.

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using Visited = std::vector<int>;

using Edges = std::vector<std::vector<char>>;
using Vertices = std::vector<bool>;
struct Graph {
    Edges edges;
    Vertices vertices;
    Graph(): edges(26, std::vector<char>()), vertices(26, false) {}
    
    bool has_edge(char from, char to) const {
        int index = from - 'a';
        auto found = std::find(edges[index].begin(), edges[index].end(), to);
        return found != edges[index].end();
    }
};

static const int NOT_VISITED = 0;
static const int IN_PROGRESS = 1;
static const int VISITED = 2;

// Accepted. 4ms. Beats 16.46% of submissions, ties 82.65% of submissions.
class Solution {
public:
    // Return the number of characters in b that form a prefix of a
    int prefix_len(const std::string& a, const std::string& b) {
        for (int len = std::min(a.size(), b.size()); len > 0; --len) {
            if (a.substr(0, len) == b.substr(0,len)) { return len; }
        }
        return 0;
    }

    Graph build_graph(const Words& words) {
        Graph g;
        for (int i = 0; i < words.size(); ++i) {
            auto& word = words[i];
            
            for (auto ch : word) { g.vertices[ch-'a'] = true; }

            if (i > 0) {
                auto len = prefix_len(words[i-1], words[i]);
                if (len < words[i-1].size() && len < words[i].size()) {
                    char from = words[i-1][len], to = words[i][len];
                    if (!g.has_edge(from, to)) {
                        g.edges[from-'a'].emplace_back(to);
                    }
                }
            }
        }
        return g;
    }

    bool dfs(Graph& g, char start, Visited& visited, std::string& order) {
        int index = start - 'a';
        visited[index] = IN_PROGRESS;
        for (auto next : g.edges[index]) {
            int to = next - 'a';
            if (visited[to] == NOT_VISITED) {
                if (dfs(g, next, visited, order) == false) {
                    return false;
                }
            } else if (visited[to] == IN_PROGRESS) {
                return false; // cycle!
            }
        }
        order.insert(order.begin(), start);
        visited[index] = VISITED;
        return true;
    }

    std::string alienOrder(const Words& words) {        
        std::string order;
        Graph g = build_graph(words);

        Visited visited(26, NOT_VISITED);
        for (int i = 0; i < g.vertices.size(); ++i) {
            auto ch = 'a' + i;
            if (g.vertices[i] && !visited[i] && dfs(g, ch, visited, order) == false) { return std::string(); }
        }
        return order;
    }
};

bool test_alien_order(Words words, std::string expected_order) {
    Solution soln;
    return soln.alienOrder(words) == expected_order;
}

void test_alien_order() {
    assert(test_alien_order({"z", "x"}, "zx"));    
    assert(test_alien_order({"z", "x", "z"}, ""));
    assert(test_alien_order({"wrt", "wrf", "er", "ett", "rftt"}, "wertf"));
}

int main(int argc, char** argv) {
    test_alien_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}