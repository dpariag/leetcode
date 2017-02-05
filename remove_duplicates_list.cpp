// Leetcode: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
// Given a sorted linked list, delete all duplicates such that each element appear only once.
// Example: Given 1->1->2, return 1->2. Given 1->1->2->3->3, return 1->2->3.

// Brute Force:
// Better:

#include "list.h"
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 60.52% of solutions, ties 39.48% of solutions.
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->next->val != cur->val) {
                cur = cur->next;
            } else {
                while (cur->next != nullptr && cur->next->val == cur->val) {
                    ListNode* to_delete = cur->next;
                    cur->next = to_delete->next;
                    delete to_delete;
                }
            }
        }
        return head;
    }
};

bool test_delete_duplicates(std::vector<int> values, std::vector<int> unique) {
    Solution soln;
    ListNode* list_values = nullptr, *list_unique = nullptr;
    list_insert(list_values, values);
    list_insert(list_unique, unique);
    soln.deleteDuplicates(list_values);
    return list_equal(list_values, list_unique);
}

void test_delete_duplicates() {
    assert(test_delete_duplicates({}, {}));
    assert(test_delete_duplicates({1}, {1}));
    assert(test_delete_duplicates({1,1}, {1}));
    assert(test_delete_duplicates({1,4}, {1,4}));
    assert(test_delete_duplicates({1,2,3,3,4}, {1,2,3,4}));
    assert(test_delete_duplicates({1,1,2,3,3,4,4,4,4,4,5,6,7}, {1,2,3,4,5,6,7}));
}

int main(int argc, char** argv) {
    test_delete_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
