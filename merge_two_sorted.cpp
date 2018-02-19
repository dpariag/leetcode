// Leetcode: https://leetcode.com/problems/merge-two-sorted-lists/description/
// Merge two sorted linked lists by splicing together the nodes of the input lists.

// Approach: Iterate both lists choosing the smaller node at each step. O(n+m) time

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 12ms. Beats 28.17% of submissions, ties 28.14% of submissions
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* result = nullptr, *cur1 = l1, *cur2 = l2;
        ListNode** tail = &result;

        while (cur1 != nullptr && cur2 != nullptr) {
            if (cur1->val < cur2->val) {
                *tail = cur1;
                cur1 = cur1->next;                
            } else {
                *tail = cur2;
                cur2 = cur2->next;
            }
            (*tail)->next = nullptr;
            tail = &((*tail)->next);
        }

        if (cur1 != nullptr) {
            *tail = cur1;
        } else if (cur2 != nullptr) {
            *tail = cur2;
        }
        return result;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
