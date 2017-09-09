// Leetcode: https://leetcode.com/problems/reverse-linked-list/description/ 
// Reverse a singly linked list

// Brute Force: Push list nodes onto a stack, pop stack to rebuild list in reverse. O(n) time/space
// Better: Reverse the list in place using 3 pointers. O(n) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 6ms. Beats 69.99% of submissions, ties 30.01% of submissions.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }
        ListNode* prev = head, *cur = head->next, *next = head->next->next;

        prev->next = nullptr;
        while (next != nullptr) {
            cur->next = prev;
            prev = cur;
            cur = next;
            next = next->next;
        }
        cur->next = prev;
        return cur;
    }
};

using Values = std::vector<int>;

bool test_reverse_list(Values values) {
    Solution soln;

    ListNode* l = nullptr;
    list_insert(l, values);

    ListNode* reversed = soln.reverseList(l);
    std::reverse(values.begin(), values.end());
    ListNode* expected = nullptr;
    list_insert(expected, values);
    return list_equal(reversed, expected);
}

void test_reverse_list() {
    assert(test_reverse_list({}));
    assert(test_reverse_list({1}));
    assert(test_reverse_list({1,2}));
    assert(test_reverse_list({1,2,3}));
    assert(test_reverse_list({1,2,3,4}));
    assert(test_reverse_list({1,2,3,4,5}));
}

int main(int argc, char** argv) {
    test_reverse_list();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
