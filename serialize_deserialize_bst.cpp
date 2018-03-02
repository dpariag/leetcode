// Leetcode: https://leetcode.com/problems/serialize-and-deserialize-bst/description/

// Approach: Serialize the BST using a preorder traversal. O(n) time/space
// Deserialization is simply repeated insertion. O(n*logn) time

#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 25ms. Beats 56.79% of submissions, ties < 3% of submissions.
class Codec {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string serialized;
        pre_order(root, serialized);
        return serialized;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(const std::string& buf) {
        std::istringstream input(buf);
        TreeNode* root = nullptr;

        while (input) {
            std::string item;
            input >> item;
            if (!item.empty()) {
                int value = std::stoi(item);
                bst_insert_value(root, value);
            }
        }
        return root;
    }

private:
    void pre_order(TreeNode* root, std::string& out) {
        if (root == nullptr) { return; }

        // Serialize current node
        out.append(std::to_string(root->val));
        out.append(1, ' ');

        pre_order(root->left, out);
        pre_order(root->right, out);
    }

    void bst_insert_value(TreeNode*& node, int value) {
        if (node == nullptr) {
            node = new TreeNode(value);
            return;
        }

        if (value < node->val) {
            bst_insert_value(node->left, value);
        } else {
            bst_insert_value(node->right, value);
        }
    }
};

bool test_bst_codec(std::vector<int> values) {
    TreeNode* tree = nullptr;
    bst_insert(tree, values);

    Codec codec;
    std::string data = codec.serialize(tree);
    TreeNode* new_tree = codec.deserialize(data);

    bool equals = tree_equals(tree, new_tree);
    delete tree;
    delete new_tree;
    return equals;
}

void test_bst_codec() {
    assert(test_bst_codec({}));
    assert(test_bst_codec({50}));
    assert(test_bst_codec({50,40}));
    assert(test_bst_codec({50,60}));
    assert(test_bst_codec({50,40,60}));
    assert(test_bst_codec({50,40,60,70}));
    assert(test_bst_codec({50,40,60,50}));
    assert(test_bst_codec({50,40,60,55,45}));
    assert(test_bst_codec({50,60,70,80}));
    assert(test_bst_codec({50,40,30,20}));
    assert(test_bst_codec({50,40,60,30,35,55,65}));
}

int main(int argc, char** argv) {
    test_bst_codec();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
