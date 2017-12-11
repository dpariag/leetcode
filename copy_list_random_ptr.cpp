// Leetcode: https://leetcode.com/problems/copy-list-with-random-pointer/description/
// Copy a linked list in which each node has an additional pointer which can be null or 
// which can point to any node in the list.

// Approach: Use a hash map to map nodes in the original list to nodes in the clone.
// Copy the list in a first pass, set random pointers in a 2nd pass (using the hash map)

#include <unordered_map>
#include <iostream>
#include <assert.h>

struct RandomListNode {
	int label;
 	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

using NodeMap = std::unordered_map<RandomListNode*, RandomListNode*>;

// Accepted. 49ms. Beats 46.34% of submissions, ties 20.86% of submissions.
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        NodeMap node_map;
        RandomListNode* copy = nullptr, *cur = head;;
        RandomListNode** insert;

        // Copy the list
        insert = &copy;
        while (cur != nullptr) {
            RandomListNode* new_node = new RandomListNode(cur->label);
            node_map.emplace(cur, new_node);
            (*insert) = new_node;
            insert = &(new_node->next);
            cur = cur->next;
        }

        // Iterate the list and it's copy setting the random pointers
        cur = head;
        auto cur_copy = copy;
        while (cur != nullptr && cur_copy != nullptr) {
            if (cur->random != nullptr) {
                auto iter = node_map.find(cur->random);
                cur_copy->random = iter->second;
            }
            cur = cur->next, cur_copy = cur_copy->next;
        }
    	return copy;
    }
};

void test_copy_random_list() {
    auto first = new RandomListNode(10);
    auto second = new RandomListNode(20);
    auto third = new RandomListNode(30);

    first->next = second;
    first->random = third;
    second->next = third;
    second->random = second;
    third->random = second;

    Solution soln;

    auto copy = soln.copyRandomList(first);
    assert(copy != first);
    assert(copy->label == 10);
    assert(copy->random->label== 30);
    
    copy = copy->next;
    assert(copy->label == 20);
    assert(copy->random->label == 20);
    
    copy = copy->next;
    assert(copy->label == 30);
    assert(copy->random->label == 20);
}

int main(int argc, char** argv) {
    test_copy_random_list();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
