// Leetcode: https://leetcode.com/problems/clone-graph/
// Clone an undirected graph. Each graph node contains a unique label and a list of its neighbors.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

// From leetcode
struct UndirectedGraphNode {
    int label;
    std::vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

using NodeMap = std::unordered_map<int, UndirectedGraphNode*>;

// Accepted. 29ms. Beats 91.38% of submissions, ties 7.6% of submissions.
class Solution {
public:
    UndirectedGraphNode* clone_graph(UndirectedGraphNode* node, NodeMap& node_map) {
        if (node == nullptr) { return nullptr; }

        auto found = node_map.find(node->label);
        if (found != node_map.end()) {
            // Already visited in the original ==> already created in the clone 
            return found->second;
        }

        // Visit the current node, then recurse on each of its neighbours (DFS)
        UndirectedGraphNode* clone = new UndirectedGraphNode(node->label);
        node_map.emplace(clone->label, clone);
        for (auto neighbor : node->neighbors) {
            clone->neighbors.emplace_back(clone_graph(neighbor, node_map));
        }
        return clone;
    }

    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        NodeMap node_map;
        return clone_graph(node, node_map);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
