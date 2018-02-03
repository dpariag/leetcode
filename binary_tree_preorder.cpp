// Leetcode: https://leetcode.com/problems/binary-tree-preorder-traversal/description/
// Given a binary tree, return the preorder traversal of its nodes' values.

// Approach: Use a stack to store the next node to be visited, visit it then emplace right/left children.

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using Stack = std::stack<TreeNode*>;

// Accepted. 3ms. Beats 0.58% of submissions, ties 55.48% of submissions.
class Solution {
public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> result;
        Stack stack;

        if (root != nullptr) { stack.push(root); }
        while (!stack.empty()) {
            auto top = stack.top();
            stack.pop();
            result.emplace_back(top->val);
            if (top->right != nullptr) { stack.push(top->right); }
            if (top->left != nullptr) { stack.push(top->left); }
        }
        return result;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
