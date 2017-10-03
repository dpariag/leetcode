// Leetcode: https://leetcode.com/problems/palindrome-linked-list/description/
// Given a singly linked list, determine if it is a palindrome.

// Brute Force: For each node, scan to the 2nd half of the list to find its counterpart. O(n^2)
// Better: Reverse the first half of the list, then compare the halves. O(n) time.

#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 19ms. Beats 56.01% of submissions, ties 43.05% of submissions.
class Solution {
public:
    // Reverse the list that starts with <head>, stopping before <stop_before>
    ListNode* reverse_list(ListNode* head, ListNode* stop_before) {
        ListNode* cur = head, *prev = nullptr;
        while (cur != stop_before) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

    // Compare two lists
    bool equals(ListNode* list1, ListNode* list2) {
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val != list2->val) { return false; }
            list1 = list1->next;
            list2 = list2->next;
        }
        return list1 == nullptr && list2 == nullptr;
    }

    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return true; }

        // Find the mid-point of the list
        int num_nodes = 1;
        ListNode* slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            ++num_nodes;
            fast = fast->next;
            if (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next;
                ++num_nodes;
            }
        }

        // Reverse the first half of the list. Odd and even cases are slightly different.
        ListNode* first_half = nullptr;
        auto second_half = slow->next;
        if (num_nodes % 2 == 0) {
            first_half = reverse_list(head, slow->next);
        } else {
            first_half = reverse_list(head, slow);
        }
        // Compare the 2nd half of the list with the reversed first half
        return equals(first_half, second_half);
    }
};

bool test_is_palindrome(std::vector<int> values, bool expected) {
    Solution soln;
    ListNode* list = nullptr;
    list_insert(list, values);
    return soln.isPalindrome(list) == expected;
}

void test_is_palindrome() {
    assert(test_is_palindrome({1}, true));
    assert(test_is_palindrome({1,1}, true));
    assert(test_is_palindrome({1,2}, false));
    assert(test_is_palindrome({1,2,1}, true));
    assert(test_is_palindrome({2,2,1}, false));
    assert(test_is_palindrome({1,2,2,1}, true));
    assert(test_is_palindrome({1,2,2,2}, false));
}

int main(int argc, char** argv) {
    test_is_palindrome();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
