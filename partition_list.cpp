// Leetcode: 
// Given a linked list of integers and a value x, partition the list so that all nodes < x come 
// beforenodes >= x. Preserve the relative order of the nodes in each of the two partitions.
// Example: Given 1->4->3->2->5->2 and x = 3, return 1->2->2->4->3->5.

// Brute Force: Iterate the lists, moving values into one of two sublists. Concatenate sublists.

#include <iostream>
#include <assert.h>
#include "list.h" // contains leetcode definitions and helpers for testing/debugging

// Accepted. 6ms. Beats 19.38% of submissions, ties 69.42% of submissions
class Solution {
public:
    inline void list_append(ListNode*& head, ListNode*& tail, ListNode* to_append) {
        if (head == nullptr) {
            head = to_append;
        } else {
            tail->next = to_append;
        }
        tail = to_append;
    }

    ListNode* partition(ListNode* head, int x) {
        ListNode* less = nullptr, *greater_equal = nullptr;
        ListNode* less_tail = nullptr, *greater_equal_tail = nullptr;

        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* to_insert = cur;
            cur = cur->next;
            to_insert->next = nullptr;
            if (to_insert->val < x) {
                list_append(less, less_tail, to_insert);
            } else {
                list_append(greater_equal, greater_equal_tail, to_insert);
            }
        }
        if (less == nullptr) {
            less = greater_equal;
        } else {
            less_tail->next = greater_equal;
        }
        return less;
    }
};

bool test_partition(std::vector<int> list_values, int x, std::vector<int> expected_values) {
    Solution soln;
    ListNode* expected = nullptr, *list = nullptr;
    list_insert(list, list_values);
    list_insert(expected, expected_values);
    auto partitioned = soln.partition(list, x);
    return list_equal(partitioned, expected);
}

void test_partition() {
    assert(test_partition({}, 15, {}));
    assert(test_partition({1}, 15, {1}));
    assert(test_partition({15}, 15, {15}));
    assert(test_partition({6,1,3,7}, 5, {1,3,6,7}));
    assert(test_partition({6,1,3,7,7,7}, 5, {1,3,6,7,7,7}));
    assert(test_partition({6,1,3,7,9,0}, 7, {6,1,3,0,7,9}));
}

int main(int argc, char** argv) {
    test_partition();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
