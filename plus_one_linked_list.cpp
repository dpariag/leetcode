// Leetcode: https://leetcode.com/problems/plus-one-linked-list/description/
// Given a non-negative integer represented as non-empty singly-linked list of digits,
// add one to the integer. The list will not contain unnecessary leading zeroes, 
// and the head of the list is the most significant digit.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 3ms. Beats 4.78% of submissions, ties 95.22% of submissions.
class Solution {
public:    
    inline ListNode* reverse(ListNode* list) {
        ListNode* prev = nullptr, *cur = list, *next = nullptr;

        while (cur != nullptr) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    ListNode* plusOne(ListNode* head) {
        ListNode* reversed = reverse(head);
        ListNode* cur = reversed;
        ListNode* prev = nullptr;

        int carry = 1;
        while (cur != nullptr) {
            int sum = cur->val + carry;
            cur->val = sum % 10;
            carry = sum / 10;
            if (carry == 0) { break; }
            prev = cur;
            cur = cur->next;
        }
        if (carry > 0) {
            ListNode* new_node = new ListNode(carry);
            prev->next = new_node;
        }
        return reverse(reversed);
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
