// Leetcode: 

// Brute Force:
// Better:

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

struct VisitNode {
    TreeNode* node = nullptr;
    bool visit = false;
    VisitNode(TreeNode*n, bool v): node(n), visit(v) {}
};
using VisitorStack = std::stack<VisitNode>;

// Accepted. 3ms. Beats 0.60% of submissions, ties 58.54% of submissions.
class Solution {
public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> result;
        VisitorStack stack;

        if (root != nullptr) {
            stack.emplace(root, false);
        }

        while (!stack.empty()) {
            auto top = stack.top();
            stack.pop();

            if (top.visit) {
                result.emplace_back(top.node->val);
            } else {
                stack.emplace(top.node, true);
                if (top.node->right != nullptr) stack.emplace(top.node->right, false);
                if (top.node->left != nullptr) stack.emplace(top.node->left, false);
            }
        }
        return result;
    }
};

bool test_post_order(std::vector<int> values, std::vector<int> expected) {
    TreeNode* root = nullptr;
    bst_insert(root, values);

    Solution soln;
    auto traversal = soln.postorderTraversal(root);
    return traversal == expected;
}

void test_post_order() {
    assert(test_post_order({}, {}));
    assert(test_post_order({10}, {10}));
    assert(test_post_order({10,5}, {5,10}));
    assert(test_post_order({10,5,15}, {5,15,10}));
    assert(test_post_order({10,5,15,1}, {1,5,15,10}));
    assert(test_post_order({10,5,15,6}, {6,5,15,10}));
    assert(test_post_order({10,5,15,20}, {5,20,15,10}));
    assert(test_post_order({10,5,15,20,18}, {5,18,20,15,10}));
}

int main(int argc, char** argv) {
    test_post_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}