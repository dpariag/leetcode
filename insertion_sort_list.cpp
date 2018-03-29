// Leetcode: https://leetcode.com/problems/insertion-sort-list/description/
// Sort a linked list using insertion sort.

// Approach: Canonical stable insertion sort. O(n^2) time.

#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 46ms. Beats 72.67% of submissions.
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* result = nullptr;

        while (head != nullptr) {
            // Pop the head of the list
            ListNode* node = head;
            head = head->next;

            // Insert into the right spot in result
            ListNode* cur = result;
            ListNode** prev = &result;
            while (cur != nullptr && cur->val <= node->val) {
                prev = &(cur->next);
                cur = cur->next;
            }
            *prev = node;
            node->next = cur;
        }
        return result;
    }
};

// Does not test that sort is stable
bool test_insertion_sort(std::vector<int> values) {
  Solution soln;

  auto sorted_values = values;
  std::sort(sorted_values.begin(), sorted_values.end());  

  ListNode* l1 = nullptr, *expected = nullptr;
  list_insert(l1, values);
  list_insert(expected, sorted_values);

  auto sorted_list = soln.insertionSortList(l1);
  return list_equal(sorted_list, expected);
}

void test_insertion_sort() {
    assert(test_insertion_sort({}));
    assert(test_insertion_sort({4}));
    assert(test_insertion_sort({5,4}));
    assert(test_insertion_sort({5,4,6}));
    assert(test_insertion_sort({5,4,6,10,1}));
    assert(test_insertion_sort({5,4,6,10,1,10,10}));
}

int main(int argc, char** argv) {
    test_insertion_sort();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}