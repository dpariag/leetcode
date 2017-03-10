// Leetcode: https://leetcode.com/problems/binary-tree-level-order-traversal/?tab=Description
// Given a binary tree, return the level order traversal of its nodes' values.
// (i.e., left to right, level by level).

// Brute Force: Build each list by repeatedly traversing to distances 0,1,2,... from the root.
// O(n^2) time for an unbalanced tree, O(n*logn) for a balanced tree.
// Better: Traverse the tree once (e.g., a pre-order traversal) tracking the level of each node,
// and appending it to the appropriate list once it is visited.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using LevelTraversal = std::vector<std::vector<int>>;

// Accepted. 6ms. Beats 19.05% of solutions and ties  64.88% of solutions.
class Solution {
public:
    LevelTraversal levelOrder(TreeNode* root) {
        LevelTraversal levels;
        traverse_levels(root, levels, 0);
        return levels;
    }

    void traverse_levels(TreeNode* node, LevelTraversal& levels, int level) {
        if (node == nullptr) { return; }

        // Visit the current node
        if (level == levels.size()) { levels.emplace_back(std::vector<int>()); }
        levels[level].emplace_back(node->val);

        traverse_levels(node->left, levels, level + 1);
        traverse_levels(node->right, levels, level + 1);
    }
};

bool test_level_order(const std::vector<int>& values, LevelTraversal expected) {
    Solution soln;
    TreeNode* tree = nullptr;
    bst_insert(tree, values);
    auto traversal = soln.levelOrder(tree);
    delete tree;
    return traversal == expected;
}

void test_level_order() {
    assert(test_level_order({10,5,17,4,18}, {{10}, {5,17}, {4,18}}));
    assert(test_level_order({10,5,17,6,18}, {{10}, {5,17}, {6,18}}));
    assert(test_level_order({10,5,17,6,18,35}, {{10}, {5,17}, {6,18},{35}}));
    assert(test_level_order({10,5,16,6,18,35,17}, {{10}, {5,16}, {6,18},{17,35}}));
}

int main(int argc, char** argv) {
    test_level_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
