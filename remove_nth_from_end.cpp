// Leetcode: https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
// Given a linked list, remove the nth node from the end of list and return its head.

// Brute Force: Traverse the list to find its length, then again to remove the n'th last node.
// Better: Traverse the list once with two pointers, one n-steps ahead of the other.

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 6ms. Beats 48.83% of submissions, ties 48.69% of submissions.
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // First pointer skips ahead by n-steps
        ListNode** cur = &head;
        int hops = 0;
        while (hops < n && *cur != nullptr) {
            cur = &(*cur)->next;
            ++hops;
        }

        // Second pointer follows the first until the first hits the list's end
        ListNode** to_remove = &head;
        while (*cur != nullptr) {
            cur = &(*cur)->next;
            to_remove = &(*to_remove)->next;
        }
        ListNode* temp = *to_remove;
        *to_remove = (*to_remove)->next;
        delete temp;
        return head;
    }
};

using Values = std::vector<int>;
bool test_remove_nth(Values values, int n, Values expected) {
    Solution soln;
    ListNode* list = nullptr;
    list_insert(list, values);
    auto cur = soln.removeNthFromEnd(list, n);

    int i = 0;
    while (cur != nullptr && i < expected.size()) {
        if (cur->val != expected[i]) { return false; }
        ++i, cur = cur->next;
    }
    return cur == nullptr && i == expected.size();
}

void test_remove_nth() {
    assert(test_remove_nth({1}, 1, {}));
    assert(test_remove_nth({1,2}, 1, {1}));
    assert(test_remove_nth({1,2}, 2, {2}));
    assert(test_remove_nth({1,2,3,4}, 1, {1,2,3}));
    assert(test_remove_nth({1,2,3,4}, 2, {1,2,4}));
    assert(test_remove_nth({1,2,3,4}, 3, {1,3,4}));
    assert(test_remove_nth({1,2,3,4}, 4, {2,3,4}));
}

int main(int argc, char** argv) {
    test_remove_nth();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
