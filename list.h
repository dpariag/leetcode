#ifndef LIST_H
#define LIST_H
#include <vector>

// List node definition used by LeetCode.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void print(const ListNode* list) {
    while (list != nullptr) {
        std::cout << list->val << " ";
        list = list->next;
    }
    std::cout << std::endl;
}

void list_insert(ListNode*& list, int value) {
    ListNode* new_node = new ListNode(value);

    if (list == nullptr) {
        list = new_node;
    } else {
        // insert at front
        new_node->next = list;
        list = new_node;
    }
}

void list_insert(ListNode*& list, const std::vector<int>& values) {
    std::vector<int> copy(values);

    std::reverse(copy.begin(), copy.end());
    for (auto val : copy) {
        list_insert(list, val);
    }
}

#endif //LIST_H
