// Leetcode: https://leetcode.com/problems/swap-nodes-in-pairs/#/description
// Given a linked list, swap every two adjacent nodes and return its head.
// Example: Given 1->2->3->4, return 2->1->4->3. You may not modify node values.

// Brute Force:
// Better:

#include "list.h"  
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 30.68% of submissions, ties 69.32% of submissions.
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode** updated_head = &head;
        auto first = head, second = head->next;

        while (first && second) {
            first->next = second->next;
            second->next = first;
            *updated_head = second;
            updated_head = &first->next;

            first = first->next;
            if (first) { second = first->next; }
        }
        return head;
    }
};

bool test_swap_pairs(std::vector<int> values, std::vector<int> expected_values) {
    Solution soln;
    
    ListNode* head = nullptr;
    list_insert(head, values);
    
    ListNode* expected = nullptr;
    list_insert(expected, expected_values);

    auto swapped = soln.swapPairs(head);
    return list_equal(swapped, expected);
}

void test_swap_pairs() {
    assert(test_swap_pairs({},{}));
    assert(test_swap_pairs({1},{1}));
    assert(test_swap_pairs({1,2},{2,1}));
    assert(test_swap_pairs({1,2,3},{2,1,3}));
    assert(test_swap_pairs({1,2,3,4},{2,1,4,3}));
    assert(test_swap_pairs({1,2,3,4,5},{2,1,4,3,5}));
    assert(test_swap_pairs({1,2,3,4,5,6},{2,1,4,3,6,5}));
}

int main(int argc, char** argv) {
    test_swap_pairs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
