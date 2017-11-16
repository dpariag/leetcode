// Leetcode: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/#/description
// Given a binary tree, return the zigzag level order traversal of its node values 
// (i.e., left to right for level #0, right to left for level #1, and so on).

// Brute Force: Traverse from root to depth 0,1,2...Reverse the order of alternate levels. O(n^2)
// Better: Do a single pre-order traversal, storing nodes by level. Reverse alternate levels. O(n)

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "tree_node.h"

using Level = std::vector<int>;
using Levels = std::vector<Level>;

// Accepted. 3ms. Beats 28.58% of submissions, ties 71.42% of submissions.
class Solution {
public:
    void pre_order_levels(TreeNode* node, Levels& levels, int level, int node_index) {
        if (node == nullptr) { return; }

        if (level > int(levels.size()) - 1) {
            levels.push_back(Level());
        }

        levels[level].emplace_back(node->val);
        pre_order_levels(node->left,  levels, level+1, node_index*2);
        pre_order_levels(node->right, levels, level+1, node_index*2 + 1);
    }

    Levels zigzagLevelOrder(TreeNode* root) {
        Levels levels;
        pre_order_levels(root, levels, 0, 0);

        for (int level = 0; level < levels.size(); ++level) {
            if (level % 2) {
                std::reverse(levels[level].begin(), levels[level].end());
            }
        }
        return levels;
    }
};

bool test_zigzag(const std::vector<int>& values, const Levels& expected) {
    Solution soln;
    TreeNode* root = nullptr;
    bst_insert(root, values);
    auto zig_zag_traversal = soln.zigzagLevelOrder(root);
    return zig_zag_traversal == expected;
}

void test_zigzag() {
    assert(test_zigzag({10}, {{10}}));
    assert(test_zigzag({10,15}, {{10},{15}}));
    assert(test_zigzag({10,5,15}, {{10},{15,5}}));
    assert(test_zigzag({10,5,15,12}, {{10},{15,5},{12}}));
    assert(test_zigzag({10,5,3,15,12}, {{10},{15,5},{3,12}}));
    assert(test_zigzag({10,5,3,8,15,12,25,1,50}, {{10},{15,5},{3,8,12,25},{50,1}}));
}

int main(int argc, char** argv) {
    test_zigzag();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
