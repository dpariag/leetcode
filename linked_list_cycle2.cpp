// Leetcode: https://leetcode.com/problems/linked-list-cycle-ii/description/
// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

// Brute Force: Iterate the list, storing node pointers in a hash map.
// A cycle exists if we encounter a node that is already in the hash map.
// Better: Use a "slow" and "fast" pointer to iterate the list. If they meet, then the list
// must contain a cycle 'k' nodes into the list. See below for how to determine 'k'

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 9ms. Beats 39.05% of submissions, ties 60.95% of submissions.
class Solution {
public:
    ListNode* detectCycle(ListNode *head) {
        ListNode* slow = head, *fast = head;
        // fast pointer moves twice as fast as slow pointer.
        do {
            if (slow != nullptr) slow = slow->next;
            if (fast != nullptr) fast = fast->next;
            if (fast != nullptr) fast = fast->next;
        } while (slow != fast);
        if (slow == nullptr && fast == nullptr) { return nullptr; } // no cycle

        // Slow and fast pointers have met, meaning a cycle exists.
        slow = head;
        while (fast != slow) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};

ListNode* make_cyclic_list(int length, int cycle_start) {
    ListNode* head = nullptr;
    if (cycle_start < length) {
        // Build a list
        ListNode* tail = nullptr;
        for (int i = length-1 ; i >= 0; --i) {
            if (head == nullptr) {
                head = new ListNode(i);
                tail = head;
            } else {
                ListNode* cur = new ListNode(i);
                cur->next = head;
                head = cur;
            }
        }
        // Now add a cycle
        ListNode* cur = head;
        for (int i = 0; i < cycle_start; ++i) { cur = cur->next; }
        tail->next = cur;
    }
    return head;
}

bool test_detect_cycle(int length, int start_cycle_after) {
    ListNode * list = make_cyclic_list(length, start_cycle_after);
    Solution soln;
    auto cycle_start = soln.detectCycle(list);
    return cycle_start->val == start_cycle_after;
}

void test_detect_cycle() {
    assert(test_detect_cycle(1, 0));
    assert(test_detect_cycle(2, 0));
    assert(test_detect_cycle(2, 1));
    assert(test_detect_cycle(10, 0));
    assert(test_detect_cycle(10, 1));
    assert(test_detect_cycle(10, 2));
    assert(test_detect_cycle(10, 3));
    assert(test_detect_cycle(10, 4));
    assert(test_detect_cycle(10, 5));
    assert(test_detect_cycle(10, 9));
}

int main(int argc, char** argv) {
    test_detect_cycle();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
