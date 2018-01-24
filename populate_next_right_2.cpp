
// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// From leetcode
struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};


// Accepted. 28ms. Beats 27.02% of submissions, ties < 1% of submissions
class Solution {
public:
    TreeLinkNode* get_next(TreeLinkNode* node, TreeLinkNode* parent) {
        if (node == nullptr || parent == nullptr) { return nullptr; }

        if (node == parent->left && parent->right != nullptr) {
            return parent->right;
        }

        TreeLinkNode* cur = parent->next;
        while (cur != nullptr) {
            if (cur->left != nullptr) { return cur->left; }
            if (cur->right != nullptr) { return cur->right; }
            cur = cur->next;
        }
        return nullptr;
    }

    void connect(TreeLinkNode* root, TreeLinkNode* parent) {
        if (root == nullptr) { return; }

        root->next = get_next(root, parent);

        connect(root->right, root);
        connect(root->left, root);
    }

    void connect(TreeLinkNode *root) {
        connect(root, nullptr);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
