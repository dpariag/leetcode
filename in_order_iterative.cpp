// Leetcode: https://leetcode.com/problems/binary-tree-inorder-traversal/#/description
// Given a binary tree, return the inorder traversal of its nodes' values. Do not use recursion.

// Brute Force: N/A
// Better: Use a stack to store the next nodes to be visited. 

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct VisitorState {
    TreeNode* node = nullptr;
    bool visit = false;
    VisitorState(TreeNode* n) : node(n), visit(false) {}
};


// Accepted. 3ms. Beats 2.18% of submissions, ties 72.11% of submissions
class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> values;
        std::stack<VisitorState> to_visit;

        if (root == nullptr) { return values; }
        to_visit.push(VisitorState(root));

        while (!to_visit.empty()) {
            VisitorState v = to_visit.top();
            to_visit.pop();

            if (v.visit) {
                values.emplace_back(v.node->val);
                continue;
            }
            if (v.node->right != nullptr) {
                to_visit.push(VisitorState(v.node->right));
            }
            v.visit = true;
            to_visit.push(v);
            if (v.node->left != nullptr) {
                to_visit.push(VisitorState(v.node->left));
            }
        }
        return values;
    }
};

bool test_in_order(std::vector<int> values, std::vector<int> expected_order) {
    Solution soln;
    TreeNode* root = nullptr;

    bst_insert(root, values);
    auto order = soln.inorderTraversal(root);
    return order == expected_order;
}

void test_in_order() {
    assert(test_in_order({}, {}));
    assert(test_in_order({1}, {1}));
    assert(test_in_order({2,1}, {1,2}));
    assert(test_in_order({2,1,3}, {1,2,3}));
    assert(test_in_order({12,1,30,-10,5,15}, {-10,1,5,12,15,30}));
}

int main(int argc, char** argv) {
    test_in_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
