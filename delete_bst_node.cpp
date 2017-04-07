// Leetcode: https://leetcode.com/problems/delete-node-in-a-bst/#/description
// Given a root node reference of a BST and a key, delete the node with the given key. 
// Return the root node reference (possibly updated) of the BST.

// Approach: Find the node using binary search. If it is a leaf, delete it. If not, swap it with
// it's in-order successor (leftmost node of right subtree) and recursively delete the node.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"
#include "stdio.h"

enum class ChildType { None, Left, Right };

class Solution {
public:
    inline void delete_node(TreeNode* node) {
        node->left = nullptr;
        node->right = nullptr;
        delete node;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        ChildType childType = ChildType::None;
        TreeNode* node = root, *parent = nullptr;
        while (node != nullptr) {
            if (key == node->val) {
                break;
            } else if (key < node->val) {
                parent = node;
                node = node->left;
                childType = ChildType::Left;
            } else {
                parent = node;
                node = node->right;
                childType = ChildType::Right;
            }
        }

        if (node == nullptr) {
            // key not found
            return root;
        } else if (parent == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr && node->right == nullptr) {
            // key found in a leaf node
            TreeNode** parent_ptr = (childType == ChildType::Left) ? &(parent->left) : &(parent->right);
            *parent_ptr = nullptr;
            delete node;
            return root;
        } else if (node->left == nullptr && node->right != nullptr) {
            // Node has only a right subtree
            TreeNode*& parent_ptr = (childType == ChildType::Left) ? parent->left : parent->right;
            parent_ptr = node->right;
            delete_node(node);
            return root;
        } else if (node->left != nullptr && node->right == nullptr) {
            // Node has only a left subtree
            TreeNode*& parent_ptr = (childType == ChildType::Left) ? parent->left : parent->right;
            parent_ptr = node->left;
            delete_node(node);
            return root;
        } else {
            // Node has left and right subtrees.
            // Swap node with it's in-order successor, then remove the successor
            TreeNode* succ = node->right, *parent = node;
            while (succ != nullptr && succ->left != nullptr) {
                parent = succ;
                succ = succ->left;
            }
            std::swap(node->val, succ->val);
            parent->left = nullptr;
            delete succ;
        }
        return root;
    }
};

bool test_bst_delete(std::vector<int> values, int to_delete, std::vector<int> expected) {
    TreeNode* tree = nullptr;
    bst_insert(tree, values);

    TreeNode* expected_tree = nullptr;
    bst_insert(expected_tree, expected);

    Solution soln;
    tree = soln.deleteNode(tree, to_delete);
    return tree_equals(tree, expected_tree);
}

void test_bst_delete() {
    assert(test_bst_delete({}, 10, {}));
    assert(test_bst_delete({1}, 10, {1}));
    assert(test_bst_delete({20}, 20, {}));
    // Delete a leaf which is a right child
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 8,
                           {20,10,30,5,35,32,27,12}));
    // Delete a leaf which is a left child
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 32,
                           {20,10,30,5,35,27,8,12}));
    // Delete a node with just a right subtree
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 5,
                           {20,10,30,35,32,27,8,12}));
    // Delete a node with just a left subtree
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 35,
                           {20,10,30,5,32,27,8,12}));
    
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 30,
                           {20,10,32,5,35,27,8,12}));
}

int main(int argc, char** argv) {
    test_bst_delete();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
