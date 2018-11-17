// Leetcode: https://leetcode.com/problems/remove-linked-list-elements/submissions/
// Remove elements from a linked list that have a particular value

// Approach: Traverse list with prev/next pointers and remove nodes with the given value. O(n) time

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 16ms. Faster than 100% of submissions.
class Solution {
public:
  ListNode* removeElements(ListNode* head, int val) {
    ListNode* prev = head;
    ListNode* cur = head;
    while (cur != nullptr) {
      if (cur->val == val) {
        if (cur == head) {
          head = cur->next; // special case
        } else {
          prev->next = cur->next;
        }
      } else {
        prev = cur;
      }
      cur = cur->next; 
    }
    return head;
  }
};

bool test_remove_elems(std::vector<int> values, int val, std::vector<int> expected_values) {
  Solution soln;
  ListNode* list = nullptr, *expected = nullptr;
  list_insert(list, values);
  list_insert(expected, expected_values);
  list = soln.removeElements(list, val);
  return list_equal(list, expected);
}

void test_remove_elems() {
  assert(test_remove_elems({}, 1, {}));
  assert(test_remove_elems({1}, 1, {}));
  assert(test_remove_elems({3,2,1,2}, 2, {3,1}));
  assert(test_remove_elems({3,2,1,2}, 1, {3,2,2}));
  assert(test_remove_elems({3,2,1,2}, 3, {2,1,2}));
  assert(test_remove_elems({3,2,1,4}, 3, {2,1,4}));
  assert(test_remove_elems({3,2,1,4}, 4, {3,2,1}));
  assert(test_remove_elems({3,3,3,4}, 3, {4}));
  assert(test_remove_elems({3,3,3,3}, 3, {}));
}

int main(int argc, char** argv) {
  test_remove_elems();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
