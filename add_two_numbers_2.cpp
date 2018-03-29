// Leetcode: https://leetcode.com/problems/add-two-numbers-ii/description/

// Brute Force:
// Better:

#include <stack>
#include <iostream>
#include <assert.h>
#include "list.h"

using Digits = std::vector<int>;

// Accepted. 57ms. Beats 64.93% of submissions.
class Solution {
public:
    inline Digits get_digits(ListNode* l) {
        Digits d;
        d.reserve(10);
        while (l != nullptr) {
            d.emplace_back(l->val);
            l = l->next;
        }
        return d;
    }

    inline void list_push(ListNode*& l, int val) {
        ListNode* node = new ListNode(val);
        node->next = l;
        l = node;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        Digits d1 = get_digits(l1);
        Digits d2 = get_digits(l2);

        int i = d1.size()-1, j = d2.size()-1;
        ListNode* result = nullptr;
        int carry = 0;
        while (i >= 0 || j >=0) {
            int val1 = 0;
            if (i >= 0) { val1 = d1[i--]; }
            
            int val2 = 0;
            if (j >= 0) { val2 = d2[j--]; }

            int sum = val1 + val2 + carry;
            carry = sum / 10;
            list_push(result, sum % 10);
        }

        if (carry) {
            list_push(result, carry);
        }
        return result;
    }
};

bool test_add(std::vector<int> num1, std::vector<int> num2, std::vector<int> expected) {
    Solution soln;
    ListNode* l1 = nullptr, *l2 = nullptr, *expected_list = nullptr;

    list_insert(l1, num1);
    list_insert(l2, num2);
    list_insert(expected_list, expected);

    auto sum = soln.addTwoNumbers(l1, l2);
    return list_equal(sum, expected_list);
}

void test_add() {
    assert(test_add({1,1},{1,1},{2,2}));
    assert(test_add({9,9,9},{1},{1,0,0,0}));
    assert(test_add({9,9,9},{1,1},{1,0,1,0}));
    assert(test_add({9,9,9},{0},{9,9,9}));
    assert(test_add({7,2,4,3},{5,6,4},{7,8,0,7}));
}

int main(int argc, char** argv) {
    test_add();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
