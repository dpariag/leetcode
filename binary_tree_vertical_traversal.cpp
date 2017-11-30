// Leetcode: https://leetcode.com/problems/binary-tree-vertical-order-traversal/description/
// Given a binary tree, return the vertical order traversal of its node values.

// Approach: Breadth-first search from the root, recording row and column of each node.
// BFS guarantees that nodes are explored top to bottom, left to right.
// No other traversal (in-order, post-order, pre-order) guarantees correct ordering in one pass.

#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct NodeEntry {
    TreeNode* node;
    int col;
    NodeEntry(TreeNode* n, int c) : node(n), col(c) {}
};
using Queue = std::queue<NodeEntry>;
using Traversal = std::vector<std::vector<int>>;

// Accepted. 3ms. Beats 13.41% of submissions, ties 86.59% of submissions.
class Solution {
public:
    Traversal bfs(TreeNode* root) {
        int min_col  = std::numeric_limits<int>::max(), max_col = std::numeric_limits<int>::min();
        Traversal t;
        Queue q;

        if (root != nullptr) { q.emplace(NodeEntry(root, 0)); }

        while (!q.empty()) {
            auto& entry = q.front();
            if (entry.col < min_col) {
                t.insert(t.begin(), std::vector<int>());
            } else if (entry.col > max_col) {
                t.push_back(std::vector<int>());
            }
            min_col = std::min(min_col, entry.col);
            max_col = std::max(max_col, entry.col);
            t[entry.col - min_col].push_back(entry.node->val);
            
            if (entry.node->left != nullptr) { q.emplace(NodeEntry(entry.node->left, entry.col-1));}
            if (entry.node->right != nullptr) { q.emplace(NodeEntry(entry.node->right, entry.col+1));}
            q.pop();
        }
        return t;
    }

    Traversal verticalOrder(TreeNode* root) {
        return bfs(root);
    }
};

using Values = std::vector<int>;

bool test_vertical_order(Values values, Traversal expected) {
    Solution soln;
    TreeNode* tree = nullptr;

    bst_insert(tree, values);
    auto traversal = soln.verticalOrder(tree);
    return traversal == expected;
}

void test_vertical_order() {
    assert(test_vertical_order({10},  {{10}}));
    assert(test_vertical_order({10,5},  {{5},{10}}));
    assert(test_vertical_order({10,5,15},  {{5},{10},{15}}));
    assert(test_vertical_order({100,50,150,20,75,70,65,130,120,125,160},
                               {{20,65},{50,70,120},{100,75,130,125},{150},{160}}));
}

int main(int argc, char** argv) {
    test_vertical_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
