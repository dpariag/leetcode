// Leetcode: https://leetcode.com/problems/reorder-list/#/description
// Given a singly linked list L: L0→L1→…→Ln-1→Ln, reorder it in-place to: L0→Ln→L1→Ln-1→L2→Ln-2→…
// Example: Given {1,2,3,4}, reorder it to {1,4,2,3}.

// Brute Force: For the i'th list node, iterate to the last node, remove it and insert it at 
// position i+1. O(n^2) time and O(1) space.
// Better: Split list into halves, reverse the 2nd half, weave halves together O(n) time, O(1) space

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 59ms. Beats 42.12% of submissions. Ties 13.23% of submissions.
class Solution {
public:

    ListNode* split(ListNode* head) {
        if (head == nullptr) { return nullptr; }

        ListNode* slow = head, *fast = head;
        while (fast->next != nullptr) {
            fast = fast->next;
            if (fast->next != nullptr) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        ListNode* second_half = slow->next;
        slow->next = nullptr;
        return second_half;
    }

    ListNode* reverse(ListNode* head) {
        if (head == nullptr) { return nullptr; }
        ListNode* prev = nullptr, *cur = head, *next = head->next;

        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    void weave(ListNode* list1, ListNode* list2) {
        ListNode* cur1 = list1, *cur2 = list2;

        while (cur2 != nullptr) {
            ListNode* prev1 = cur1;
            cur1 = cur1->next;
            ListNode* prev2 = cur2;
            cur2 = cur2->next;

            prev1->next = prev2;
            prev2->next = cur1;
        }
    }

    void reorderList(ListNode* head) {
        ListNode* second_half = split(head);
        second_half = reverse(second_half);
        weave(head, second_half);
    }
};

bool test_reorder(const std::vector<int>& values, const std::vector<int>& expected_values) {
    Solution soln;
    ListNode* list = nullptr, *expected = nullptr;
    list_insert(list, values);
    list_insert(expected, expected_values);

    soln.reorderList(list);
    return list_equal(list, expected);
}

void test_reorder() {
    assert(test_reorder({}, {}));
    assert(test_reorder({1}, {1}));
    assert(test_reorder({1,2}, {1,2}));
    assert(test_reorder({1,2,3}, {1,3,2}));
    assert(test_reorder({1,2,3,4}, {1,4,2,3}));
    assert(test_reorder({1,2,3,4,5}, {1,5,2,4,3}));
}

int main(int argc, char** argv) {
    test_reorder();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
