// Leetcode: https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/
// Given a BST, find the kth smallest element in the BST

// Brute Force: In-order traversal, counting nodes visited. Return the k'th value. O(k) time.
// Better: Label each node with the number of nodes in its left subtree, use that information
// to traverse from the root. O(logN) time. Did not implement this.

#include <vector>
#include <iostream>
#include <assert.h>
#include "tree_node.h"

// Accepted. 12ms. Beats 97.19% of submissions, ties 2.81% of submissions.
class Solution {
public:
    void kth_smallest(TreeNode* root, int k, int& cur, int& result) {
        if (cur < k && root->left != nullptr) {
            kth_smallest(root->left, k, cur, result);
        }
        ++cur;
        if (cur == k) { result = root->val; }

        if (cur < k && root->right != nullptr) {
            kth_smallest(root->right, k, cur, result);
        }
    }

    int kthSmallest(TreeNode* root, int k) {
        int cur = 0;
        int result = 0;
        kth_smallest(root, k, cur, result);
        return result;
    }
};

bool test_kth_smallest(std::vector<int> values, int k, int expected) {
    Solution soln;
    TreeNode* root = nullptr;
    bst_insert(root, values);
    return soln.kthSmallest(root, k) == expected; 
}

void test_kth_smallest() {
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 1, 1));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 2, 5));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 3, 6));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 4, 10));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 5, 11));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 6, 12));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 7, 14));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 8, 15));
    assert(test_kth_smallest({15,10,25,5,12,1,6,11,14}, 9, 25));
}

int main(int argc, char** argv) {
    test_kth_smallest();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
