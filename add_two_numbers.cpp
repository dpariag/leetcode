// Leetcode: https://leetcode.com/problems/add-two-numbers/description/
// Given two non-empty linked lists representing non-negative integers, return their sum.
// Digits are stored in reverse order and each list node contains a single digit.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 49ms. Beats 47.49% of submissions, ties 8.16% of submissions.
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = nullptr;
        ListNode** tail = &result;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr) {
            auto l1_digit = (l1 != nullptr) ? l1->val : 0;
            auto l2_digit = (l2 != nullptr) ? l2->val : 0;

            auto sum = l1_digit + l2_digit + carry; 
            ListNode* new_node = new ListNode(sum % 10);
            carry = sum / 10;
            *tail = new_node;

            tail = &(new_node->next);
            if (l1 != nullptr) {l1 = l1->next;}
            if (l2 != nullptr) {l2 = l2->next;}
        }
        if (carry > 0) {
            ListNode* new_node = new ListNode(carry);
            *tail = new_node;
        }
        return result;
    }
};

bool test_add(std::vector<int> first, std::vector<int> second, std::vector<int> expected) {
    Solution soln;
    ListNode* l1 = nullptr, *l2 = nullptr, *expected_result = nullptr;

    list_insert(l1, first);
    list_insert(l2, second);
    list_insert(expected_result, expected);

    auto result = soln.addTwoNumbers(l1, l2);
    return list_equal(expected_result, result);
}

void test_add() {
    assert(test_add({1}, {1}, {2}));
    assert(test_add({9}, {1}, {0,1}));
    assert(test_add({9}, {9}, {8,1}));
    assert(test_add({9}, {0}, {9}));
    assert(test_add({0}, {0}, {0}));
    assert(test_add({2,4,3}, {5,6,4}, {7,0,8}));
    assert(test_add({9,9}, {9,9}, {8,9,1}));
}


int main(int argc, char** argv) {
    test_add();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
