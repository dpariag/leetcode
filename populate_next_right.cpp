// Leetcode: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/
// Populate each next pointer to point to its next right node. If there is no next right node,
// the next pointer should be set to NULL.

// Approach: Do a preorder traversal of the tree passing parent pointers to each call.
// During the preorder traversal, the next pointer is set as follows:
// i) if the node is a left child, set the next pointer to the parent's right child.
// ii) if the node is a right child set the next ptr to the left child of the parent's next

#include <iostream>
#include <assert.h>

// From leetcode
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// Accepted. 23ms. Beats 12.41% of submissions, ties 5.63% of submissions
class Solution {
public:
    // Based on a pre-order traversal
    void connect(TreeLinkNode* root, TreeLinkNode* parent, TreeLinkNode* next) {
        if (root == nullptr) { return; }

        if (next != nullptr) {
            root->next = next;
        } else if (parent != nullptr && parent->next != nullptr) {
            root->next = parent->next->left;
        }

        connect(root->left, root, root->right);
        connect(root->right, root, nullptr);
    }

    void connect(TreeLinkNode *root) {
        connect(root, nullptr, nullptr);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}