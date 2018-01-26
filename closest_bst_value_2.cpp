// Leetcode: https://leetcode.com/problems/closest-binary-search-tree-value-ii/description/
// Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

// Brute Force: Traverse the BST copying values to an array. Solve the problem using the array. O(n) time.
// Better: Locate the closest value to the target using binary search. Perform BFS using a min-heap,
// keyed by difference from the target. For each node de-queued, add it's successor and predecessor to the heap.

#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <assert.h>
#include "tree_node.h"

struct NodeInfo {
    TreeNode* node = nullptr;
    double distance = 0.0;
    NodeInfo(TreeNode* n, double d): node(n), distance(d) {}
    bool operator>(const NodeInfo& other) const { return distance > other.distance; }
};

using MinHeap = std::priority_queue<NodeInfo, std::vector<NodeInfo>, std::greater<NodeInfo>>;
using Visited = std::unordered_set<TreeNode*>;

// Accepted. 16ms. Beats 13.39% of submissions, ties 26.34% of submissions.
class Solution {
public:
    std::vector<int> closestKValues(TreeNode* root, double target, int k) {        
        Visited visited;
        MinHeap min_heap;
        TreeNode* cur = root;

        while (cur != nullptr) {
            min_heap.emplace(cur, std::abs(target - double(cur->val)));
            visited.emplace(cur);
            cur = (target < double(cur->val)) ? cur->left : cur->right;
        }

        std::vector<int> result;
        while (!min_heap.empty() && result.size() < k) {
            auto closest = min_heap.top();
            min_heap.pop();

            result.emplace_back(closest.node->val);

            // Add predecessor if it's not a parent
            TreeNode* left = closest.node->left;
            while(left != nullptr) {
                if (visited.count(left) == 0) {
                    min_heap.emplace(left, std::abs(target - double(left->val)));
                    visited.emplace(left);
                }                
                left = left->right;
            }

            // Add successor if it's not a parent
            TreeNode* right = closest.node->right;
            while (right != nullptr) {
                if (visited.count(right) == 0) {
                    min_heap.emplace(right, std::abs(target - double(right->val)));
                    visited.emplace(right);
                }                
                right = right->left;
            }
        }
        return result;
    }
};

using Values = std::vector<int>;

bool test_closest_k_values(TreeNode* root, double target, int k, Values expected) {
    Solution soln;
    auto closest = soln.closestKValues(root, target, k);
    std::sort(closest.begin(), closest.end());
    return closest == expected;
}

void test_closest_k_values() {
    TreeNode* root = nullptr;
    bst_insert(root, {20,10,40,2,15,26,45,25});

    assert(test_closest_k_values(root, 16.0, 1, {15}));
    assert(test_closest_k_values(root, 16.0, 2, {15,20}));
    assert(test_closest_k_values(root, 16.0, 3, {10,15,20}));
    assert(test_closest_k_values(root, 16.0, 4, {10,15,20,25}));
    assert(test_closest_k_values(root, 16.0, 5, {10,15,20,25,26}));
}


int main(int argc, char** argv) {
    test_closest_k_values();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
