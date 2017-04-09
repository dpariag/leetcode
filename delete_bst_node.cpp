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

// Accepted. 36ms. Beats 65.86% of submissions, ties 18.88% of submissions
class Solution {
public:
    inline void delete_node(TreeNode* node, TreeNode** parent_ptr, TreeNode* new_child) {
        *parent_ptr = new_child;
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

        TreeNode** parent_ptr = &root;
        if (node == nullptr) {
            // key not found
            return root;
        } else if (node->left == nullptr && node->right == nullptr) {
            // key found in a leaf node
            if (parent != nullptr) {
                parent_ptr = (childType == ChildType::Left) ? &(parent->left) : &(parent->right);
            }
            delete_node(node, parent_ptr, nullptr);
        } else if (node->left == nullptr && node->right != nullptr) {
            // Node has only a right subtree
            if (parent != nullptr) {
                parent_ptr = (childType == ChildType::Left) ? &parent->left : &parent->right;
            }
            delete_node(node, parent_ptr, node->right);
        } else if (node->left != nullptr && node->right == nullptr) {
            // Node has only a left subtree
            if (parent != nullptr) {
                parent_ptr = (childType == ChildType::Left) ? &parent->left : &parent->right;
            }
            delete_node(node, parent_ptr, node->left);
        } else {
            // Node has left and right subtrees.
            // Swap node with it's in-order successor, then remove the successor
            TreeNode* succ = node->right, *succ_parent = node;
            parent_ptr = &(node->right);
            while (succ != nullptr && succ->left != nullptr) {
                succ_parent = succ;
                succ = succ->left;
                parent_ptr = &(succ_parent->left);
            }
            int succesor_value = succ->val;
            *parent_ptr = deleteNode(succ, succ->val);
            node->val = succesor_value;
        }
        return root;
    }
};

bool test_bst_delete(std::vector<int> values, int to_delete, std::vector<int> expected) {
    TreeNode* tree = nullptr;
    bst_insert(tree, values);

    std::cout << std::endl << std::endl;
    std::cout << "TREE:" << std::endl;
    print(tree);
    std::cout << "EXPECTED:" << std::endl;
    TreeNode* expected_tree = nullptr;
    bst_insert(expected_tree, expected);
    print(expected_tree);

    Solution soln;
    tree = soln.deleteNode(tree, to_delete);
    std::cout << "AFTER DELETE" << std::endl;
    print(tree);
    return tree_equals(tree, expected_tree);
}

void test_bst_delete() {
    assert(test_bst_delete({}, 10, {}));
    assert(test_bst_delete({1}, 10, {1}));
    assert(test_bst_delete({1,2}, 1, {2}));
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
    // Delete a node with two subtrees 
    assert(test_bst_delete({20,10,30,5,35,32,27,8,12}, 30,
                           {20,10,32,5,35,27,8,12}));
    
    assert(test_bst_delete({5,3,6,2,4,7}, 3,
                           {5,4,2,6,7}));
    
    assert(test_bst_delete({5,3,6,2,4,7}, 5,
                           {6,3,7,2,4}));
}

int main(int argc, char** argv) {
    test_bst_delete();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
