// Leetcode: https://leetcode.com/problems/linked-list-random-node/description/
// Given a singly linked list, return a random node's value. Each node must have the same
// probability of being chosen.

// Brute Force: Iterate the list to find its length, generate a random number over (0, length-1) 
// and iterate again to find the i'th node. O(n) time. Store the nodes in a vector to avoid the
// second pass. O(n) time and space.
// Better: Keep a candidate node (initially the first node). Iterate the list, replace the candidate
// node with the i'th node with probability 1/i for i = 2,3,...,n

#include <cstdlib>
#include <iostream>
#include <assert.h>
#include "list.h"

// Accepted. 36ms. Beats 89.41% of submissions, ties 8.33% of submissions.
class Solution {
public:
    Solution(ListNode* head): m_list(head) {
        std::srand(std::time(0));
    }


    int getRandom() {
        int val = m_list->val, count = 1;

        ListNode* cur = m_list->next;
        while (cur != nullptr) {
            ++count;
            int rand = (std::rand() % count); // 0..count-1
            if (rand == count-1) {
                // this is true with probability 1/count
                val = cur->val;
            }
            cur = cur->next;
        }
        return val;
    }

private:
    ListNode* m_list;
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
