// Leetcode: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct 
// numbers from the original list.
// Example: Given 1->2->3->3->4->4->5, return 1->2->5.  Given 1->1->1->2->3, return 2->3.

// Brute Force: Count values using a hash_map, create a new list by appending values with count = 1.
// O(n) time and space.
// Better: Iterate the list, scanning for duplicates, and appending unique values. Need to be careful// with pointer manipulation.

#include "list.h"
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 54.79% of submissions, ties 45.21%
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode** append = &head;
        ListNode* cur = head;
        
        while (cur != nullptr) {
            int count = 1;
            while (cur->next != nullptr && cur->next->val == cur->val) {
                ++count;
                cur = cur->next;
            }
            if (count == 1) {
                *append = cur;
                append = &(cur->next);
            }
            cur = cur->next;
        }
        *append = nullptr;
        return head;
    }
};

bool test_delete_duplicates(std::vector<int> values, std::vector<int> unique) {
    Solution soln;
    ListNode* list_values = nullptr;
    ListNode* unique_values = nullptr;

    list_insert(list_values, values);
    list_insert(unique_values, unique);

    list_values = soln.deleteDuplicates(list_values);
    return list_equal(list_values, unique_values);
}

void test_delete_duplicates() {
    assert(test_delete_duplicates({}, {}));
    assert(test_delete_duplicates({1}, {1}));
    assert(test_delete_duplicates({1,2,3}, {1,2,3}));
    assert(test_delete_duplicates({1,1,2,3}, {2,3}));
    assert(test_delete_duplicates({1,2,2,2,3}, {1,3}));
    assert(test_delete_duplicates({1,2,3,3,3,3}, {1,2}));
}

int main(int argc, char** argv) {
    test_delete_duplicates();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
