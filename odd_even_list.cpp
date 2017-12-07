// Leetcode: https://leetcode.com/problems/odd-even-linked-list/description/
// Given a singly linked list, group all odd-numbered nodes together followed by the even-numbered nodes. 

// Brute Force: Collect odd-numbered in one vector, and even-numbered ones in another.
// Reconstruct the target list using the two vectors. O(n) time and space.
// Better: Save space by building two separate sublists as we iterate. Concatenate them afterwards. 
// O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 13ms. Beats 93.23% of submissions, ties 5.79% of submissions.
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { return head; }

        ListNode* odd_list = nullptr, *even_list = nullptr;
        ListNode* odd_ptr = head, *even_ptr = head->next;
        ListNode** odd_tail = &odd_list, ** even_tail = &even_list;

        while (odd_ptr != nullptr) {
            *odd_tail = odd_ptr;
            odd_tail = &(odd_ptr->next);
            odd_ptr = odd_ptr->next;
            if (odd_ptr) { odd_ptr = odd_ptr->next; }

            if (even_ptr) {
                *even_tail = even_ptr;
                even_tail = &(even_ptr->next);
                even_ptr = even_ptr->next;
                if (even_ptr) { even_ptr = even_ptr->next; }
                *even_tail = nullptr;
            }            
        }
        *odd_tail = even_list;
        return odd_list;
    }
};

bool test_odd_even_list(std::vector<int> values, std::vector<int> expected) {
    Solution soln;

    ListNode* list = nullptr;
    list_insert(list, values);
    list = soln.oddEvenList(list);

    ListNode* expected_list = nullptr;
    list_insert(expected_list, expected);    
    return list_equal(list, expected_list);
}

void test_odd_even_list() {    
    assert(test_odd_even_list({1}, {1}));
    assert(test_odd_even_list({1,5}, {1,5}));
    assert(test_odd_even_list({1,5,7}, {1,7,5}));
    assert(test_odd_even_list({1,5,7,9}, {1,7,5,9}));
    assert(test_odd_even_list({1,5,7,9,11}, {1,7,11,5,9}));
    assert(test_odd_even_list({1,5,7,9,11,13}, {1,7,11,5,9,13}));
}

int main(int argc, char** argv) {
    test_odd_even_list();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
