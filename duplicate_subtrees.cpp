// Leetcode: https://leetcode.com/problems/find-duplicate-subtrees/description/
// Given a binary tree, find all duplicate subtrees. Return the keys of root node for each duplicate.

// Brute Force: For each node value, search for it elsewhere in the tree and compare subtrees. 
// Record one instance of each duplicate tree. O(n^3) time.
// Better: Iterate the tree computing a (rolling) hash of each subtree. Only compare subtrees with
// equal hashes. This is analogous to Rabin-Karp string search. O(n) expected, O(n^2) worst case.

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include "tree_node.h"

struct SubtreeData {
    TreeNode* root = nullptr;
    bool is_duplicate = false;  // have we found a duplicate of this tree?
};

using Subtrees = std::vector<SubtreeData>;
using Duplicates = std::vector<TreeNode*>;
using SubtreeHashes = std::unordered_map<size_t, Subtrees>; // hash value -> subtrees with that hash

inline void hash_combine(size_t& seed, size_t value) {
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

inline bool subtree_equal(const TreeNode* first, const TreeNode* second) {
    if (first == nullptr && second == nullptr) {
        return true;
    } else if ((first == nullptr && second != nullptr) ||
               (first != nullptr && second == nullptr)) {
        return false;
    } else {
        return first->val == second->val && 
               subtree_equal(first->left, second->left) &&
               subtree_equal(first->right, second->right);
    }
}

// Accepted. 16ms. Beats 98.93% of submissions, ties < 1% of submissions.
class Solution {
public:
    Duplicates findDuplicateSubtrees(TreeNode* root) {
        Duplicates duplicates;
        SubtreeHashes hashes;

        if (root != nullptr) {
            find_duplicates(root, hashes, duplicates);
        }
        return duplicates;
    }

    size_t find_duplicates(TreeNode* root, SubtreeHashes& hashes, Duplicates& dups) {
        size_t hash = root->val;

        if (root->left != nullptr) {
            size_t left_hash = find_duplicates(root->left, hashes, dups);
            hash_combine(hash, left_hash);
        }
        if (root->right != nullptr) { 
            size_t right_hash = find_duplicates(root->right, hashes, dups);
            hash_combine(hash, right_hash);
        }

        // Look for other subtrees with the same hash.
        // Compare root against each, but only save root if it is a "new" duplicate.
        bool found_duplicate = false;
        auto& same_hashes = hashes[hash];
        for (auto& tree_data : same_hashes) {
            if (subtree_equal(root, tree_data.root)) {
                found_duplicate = true;
                if (!tree_data.is_duplicate) {
                    dups.emplace_back(root);
                    tree_data.is_duplicate = true;
                    break;
                }
            }
        }

        if (!found_duplicate) {
            // root currently has no duplicates, save it for future comparisons
            SubtreeData data;
            data.root = root;
            hashes[hash].push_back(data);
        }
        return hash;
    }
};

bool test_duplicate_subtrees(const std::vector<int> values, std::vector<int> expected_dups) {
    Solution soln;
    TreeNode* root = nullptr;

    in_order_insert(root, values);
    auto duplicates = soln.findDuplicateSubtrees(root);
    std::vector<int> duplicate_values;

    for (auto d : duplicates) {
        duplicate_values.emplace_back(d->val);
    }

    std::sort(expected_dups.begin(), expected_dups.end());
    std::sort(duplicate_values.begin(), duplicate_values.end());
    return (duplicate_values == expected_dups);
}

void test_duplicate_subtrees() {
    assert(test_duplicate_subtrees({}, {}));
    assert(test_duplicate_subtrees({1}, {}));
    assert(test_duplicate_subtrees({1,1,1}, {1}));
    assert(test_duplicate_subtrees({1,1,2}, {}));
    assert(test_duplicate_subtrees({2,1,5,2,1}, {2,1}));
    assert(test_duplicate_subtrees({3,1,5,2,1}, {1}));
    assert(test_duplicate_subtrees({1,1,1,1,1}, {1,1}));
}

int main(int argc, char** argv) {
    test_duplicate_subtrees();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
