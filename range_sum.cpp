// Leetcode: 
// Given an integer array A, find the sum of the elements between indices i and j (i ≤ j), inclusive.
// The update(i, val) function modifies A by updating the element at index i to val.

// Brute Force: Simply store the array. sum is O(n) and update is O(1). On average, O(n)
// Better: Store the array as an annotated binary tree. sum/update are O(logN). On average, O(logN)

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 136ms. Beats 49.65% of submissions.
class NumArray {
public:
    NumArray(const std::vector<int>& nums): m_tree(nullptr) {
        build(m_tree, nums, 0, nums.size() - 1);
    }

    void update(int i, int val) {
        update(m_tree, i, val);
    }

    int sumRange(int i, int j) {
        return sum(m_tree, i, j);
    }
private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int index = 0;
        int range_start = 0; // starting index of subtree values
        int range_end = 0;   // ending index of subtree values
        int leftSum = 0;
        int rightSum = 0;
        int val;

        int sum() { return val + leftSum + rightSum; }
    };
    Node* m_tree;

    void build(Node*& node, const std::vector<int>& nums, int start, int end) {
        if (start > end) { return; }
        int mid = start + (end - start) / 2;

        if (node == nullptr) { node = new Node; }
        node->val = nums[mid];
        node->index = mid;
        node->range_start = start;
        node->range_end = end;
        
        build(node->left, nums, start, mid-1);
        build(node->right, nums, mid+1, end);

        node->leftSum = (node->left != nullptr) ? node->left->sum() : 0;
        node->rightSum = (node->right != nullptr) ? node->right->sum() : 0;
    }


    int sum(Node* node, int start, int end) {
        if (node == nullptr || start > end) { return 0; }
        if (start == node->range_start && end == node->range_end) { return node->sum(); }

        int right_start = std::max(node->index + 1, start);
        int left_end = std::min(node->index - 1, end);
        int s = sum(node->left, start, left_end) +
                sum(node->right, right_start, end); 

        if (node->index >= start && node->index <= end) {
            s += node->val;
        }
        return s;
    }
   
    int update(Node* node, int i, int val) {
        if (node == nullptr) { return 0; }

        int delta = 0;
        if (i == node->index) {
            delta = node->val - val;
            node->val = val;
        } else if (i < node->index) {
            delta = update(node->left, i, val);
            node->leftSum -= delta;
        } else {
            delta = update(node->right, i, val);
            node->rightSum -= delta;
        }
        return delta;
    }
};

void test_range_sum() {
    NumArray arr({0,1,2,3,4,5,6});
    assert(arr.sumRange(0,0) == 0);
    assert(arr.sumRange(0,1) == 1);
    assert(arr.sumRange(0,2) == 3);
    assert(arr.sumRange(0,3) == 6);
    assert(arr.sumRange(0,4) == 10);
    assert(arr.sumRange(0,5) == 15);
    assert(arr.sumRange(0,6) == 21);
    assert(arr.sumRange(1,6) == 21);
    assert(arr.sumRange(2,6) == 20);
    assert(arr.sumRange(3,6) == 18);
    assert(arr.sumRange(4,6) == 15);
    assert(arr.sumRange(5,6) == 11);
    assert(arr.sumRange(6,6) == 6);
    assert(arr.sumRange(6,6) == 6);
    assert(arr.sumRange(2,5) == 14);
    assert(arr.sumRange(1,5) == 15);

    arr.update(3, 10); // {0,1,2,10,4,5,6}
    assert(arr.sumRange(0,6) == 28);
    assert(arr.sumRange(0,3) == 13);
    assert(arr.sumRange(3,6) == 25);
    assert(arr.sumRange(0,2) == 3);
}

int main(int argc, char** argv) {
    test_range_sum();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
