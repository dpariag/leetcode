// Leetcode: https://leetcode.com/problems/rotate-list/
// Given a singly-linked list, rotate the list to the right by k places, where k is non-negative.
// Example: given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.

#include <iostream>
#include <algorithm>
#include <assert.h>
#include "list.h"   // for ListNode definition

// Brute Force: Move the last element in the list to the front of the list, k times. O(n*k)
// Better: Move the entire sublist consisting of the last (k % length) elements to the 
// front of the list. O(n) time and O(1) space.

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr) { return head; }

        // Compute the length of the list
        ListNode* cur = head;
        int length = 0;
        while (cur != nullptr) { ++length; cur = cur->next; }

        // Find the sublist consisting of the last (k % length) items
        k = k % length;
        ListNode* ahead = head;
        auto i = 0;
        while (ahead != nullptr && i < k) {
            ++i;
            ahead = ahead->next;
        }
        
        cur = head;
        while (ahead != nullptr && ahead->next != nullptr) {
            cur = cur->next;
            ahead = ahead->next;
        }

        // Move the sublist to the front of the list
        ListNode* sublist = cur->next;
        cur->next = nullptr;
        ahead->next = head;
        return sublist;
    }
};

bool test_list_rotation(const std::vector<int>& values, int k) {
    Solution soln;
    ListNode* list = nullptr;
    list_insert(list, values);

    print(list);
    list = soln.rotateRight(list, k);
   
    std::vector<int> copy(values);
    std::rotate(copy.rbegin(), copy.rbegin() + (k % values.size()), copy.rend());

    print(list);
    for (auto i = 0; i < copy.size(); ++i) {
        if (list == nullptr || copy[i] != list->val) { return false; }
        list = list->next;
    }
    return true;
}

void test_list_rotations() {
    assert(test_list_rotation({1}, 2));
    assert(test_list_rotation({1,2,3,4,5}, 2));
}

int main(int argc, char** argv) {
    test_list_rotations();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
