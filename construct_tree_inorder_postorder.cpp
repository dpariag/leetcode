// Leetcode: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

using Traversal = std::vector<int>;
using TraversalMap = std::unordered_map<int, int>;

// Accepted. 12ms. Beats 84.20% of submissions, ties 3.5% of submissions.
class Solution {
public:

    void build_tree(TreeNode*& node, Traversal& post_order, int& p_index, TraversalMap& in_order_map, int start, int end) {
        if (p_index < 0) { return; }

        int key = post_order[p_index];
        int i_index = in_order_map[post_order[p_index]];

        if (i_index < start || i_index > end) { return; }

        node = new TreeNode(key);

        --p_index;        
        build_tree(node->right, post_order, p_index, in_order_map, i_index+1, end);
        build_tree(node->left, post_order, p_index, in_order_map, start, i_index-1);
    }

    TreeNode* buildTree(Traversal& in_order, Traversal& post_order) {
        TreeNode* tree = nullptr;
        TraversalMap in_order_map;

        for (int i = 0; i < in_order.size(); ++i) {
            in_order_map[in_order[i]] = i;
        }

        int p_index = int(post_order.size()) - 1;
        build_tree(tree, post_order, p_index, in_order_map, 0, in_order.size()-1);
        return tree;
    }
};

void test_build_tree() {
    Solution soln;
    //Traversal in_order{9,3,15,20,7};
    //Traversal post_order{9,15,7,20,3};
    
    // Traversal in_order{8,4,10,2,6};
    // Traversal post_order{4,8,2,6,10};

    // Traversal in_order{3,6,10};
    // Traversal post_order{10,6,3};

    Traversal in_order{8,9,10};
    Traversal post_order{8,9,10};

    auto tree = soln.buildTree(in_order, post_order);
    print(tree);
}

int main(int argc, char** argv) {
    test_build_tree();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
