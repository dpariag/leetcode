// Leetcode: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
// Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
// (ie, from left to right, level by level from leaf to root).

// Brute Force: Build levels by repeatedly probing levels 0,1,2,.. from the root. O(n^2)
// Better: Do a pre-order traversal to accumulate the levels, then reverse the levels. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using Levels = std::vector<std::vector<int>>;

// Accepted. 6ms. Beats 16.19% of submissions, ties 51.16% of submissions.
class Solution {
public:
    void build_levels(const TreeNode* root, Levels& levels, int cur_level) {
        if (root == nullptr) { return; }

        if (cur_level >= levels.size()) {
            levels.emplace_back(std::vector<int>());
        }

        // Pre-order traversal
        levels[cur_level].emplace_back(root->val);
        build_levels(root->left, levels, cur_level+1);
        build_levels(root->right, levels, cur_level+1);
    }

    Levels levelOrderBottom(TreeNode* root) {
        Levels levels;
        build_levels(root, levels, 0);
        std::reverse(levels.begin(), levels.end());
        return levels;
    }
};

bool test_level_order_bottom(std::vector<int> values, Levels expected) {
    Solution soln;
    TreeNode* tree = nullptr;
    bst_insert(tree, values);
    auto levels = soln.levelOrderBottom(tree);
    return levels == expected;
}

void test_level_order_bottom() {
    assert(test_level_order_bottom({}, {}));
    assert(test_level_order_bottom({5}, {{5}}));
    assert(test_level_order_bottom({10,5,15}, {{5,15},{10}}));
    assert(test_level_order_bottom({10,5,15}, {{5,15},{10}}));
    assert(test_level_order_bottom({10,5,15,3,8,12}, {{3,8,12}, {5,15},{10}}));
}

int main(int argc, char** argv) {
    test_level_order_bottom();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
