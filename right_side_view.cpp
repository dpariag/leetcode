// Leetcode: https://leetcode.com/problems/binary-tree-right-side-view/description/ 
// Imagine you're standing to the right of a binary tree. Return the node values from top to bottom.

// Better: Perform a pre-order traversal of the tree, tracking the level during traversal.
// Store the most recently visited value (i.e., rightmost value) during traversal. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 3ms. Beats 16.37% of submissions, ties 83.63% of submissions.
class Solution {
public:
    // Pre-order traversal, so that values are added in level-order
    void right_side(const TreeNode* root, int level, std::vector<int>& view) {
        if (root == nullptr) { return; }

        if (level < view.size()) {
            view[level] = root->val;
        } else {
            view.emplace_back(root->val);
        }
        right_side(root->left, level+1, view);
        right_side(root->right, level+1, view);
    }

    std::vector<int> rightSideView(const TreeNode* root) {
        std::vector<int> view;
        right_side(root, 0, view);
        return view;
    }
};

bool test_right_side_view(std::vector<int> values, std::vector<int> expected_view) {
    Solution soln;
    TreeNode* tree = nullptr;
    bst_insert(tree, values);

    auto view = soln.rightSideView(tree);
    return view == expected_view;
}

void test_right_side_view() {
    assert(test_right_side_view({10,5,3,15,20}, {10,15,20}));
    assert(test_right_side_view({10,5,3,15,20,18}, {10,15,20,18}));
    assert(test_right_side_view({10,5,3,15,20,18,22}, {10,15,20,22}));
    assert(test_right_side_view({10,5,3,1}, {10,5,3,1}));
    assert(test_right_side_view({10,5,3,1,12}, {10,12,3,1}));
    assert(test_right_side_view({10,5,3,1,12,15}, {10,12,15,1}));
}

int main(int argc, char** argv) {
    test_right_side_view();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
