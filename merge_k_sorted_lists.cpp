// Leetcode: https://leetcode.com/problems/merge-k-sorted-lists/#/description
// Merge k sorted linked lists and return it as one sorted list.

// Brute Force:
// Better:

#include "list.h"
#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>

struct GreaterThan {
    bool operator()(const ListNode* node1, const ListNode* node2) {
        return node1->val > node2->val;
    }
};

using MinHeap = std::priority_queue<ListNode*, std::vector<ListNode*>, GreaterThan>;

// Accepted. 29ms. Beats 74.27% of submissions, ties 16.60% of submissions.
class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        int k = 0;
        MinHeap min_heap;
        for (auto i = 0; i < lists.size(); ++i) {
            if (lists[i] != nullptr) {
                min_heap.emplace(lists[i]);
                ++k;
            }
        }

        ListNode* result = nullptr;
        ListNode** to_append = &result;
        while (!min_heap.empty() && k > 1) {
            auto node = min_heap.top();
            min_heap.pop();
            if (node->next != nullptr) {
                min_heap.emplace(node->next);
            } else {
                --k;
            }
            node->next = nullptr;
            *to_append = node;
            to_append = &node->next;
        }
        if (k == 1 && !min_heap.empty()) {
            auto node = min_heap.top();
            min_heap.pop();
            *to_append = node;
        }
        return result;
    }
};

bool test_merge_k_lists(std::vector<std::vector<int>> input_data) {
    std::vector<ListNode*> lists;
    std::vector<int> flat_input;

    for (auto& input : input_data) {
        lists.emplace_back(nullptr);
        list_insert(lists.back(), input);
        flat_input.insert(flat_input.end(), input.begin(), input.end());
    }
    std::sort(flat_input.begin(), flat_input.end());

    Solution soln;
    auto merged = soln.mergeKLists(lists);
    auto cur = merged;
    int i = 0;
    while (cur != nullptr && i < flat_input.size()) {
        if (cur->val != flat_input[i]) { return false; }
        ++i; cur = cur->next;
    }
    return true;
}

void test_merge_k_lists() {
    assert(test_merge_k_lists({{}}));
    assert(test_merge_k_lists({{1,2,3}, {1,2}}));
    assert(test_merge_k_lists({{1,2,3}, {1,2}, {0,0,0}}));
    assert(test_merge_k_lists({{},{1,2,3}, {1,2}, {0,0,0}}));
    assert(test_merge_k_lists({{},{1,2,3}, {1,2}, {0,0,0}, {}}));
    assert(test_merge_k_lists({{},{1,2,3}, {1,2}, {0,0,0}, {100}}));
    assert(test_merge_k_lists({{},{1,2,3}, {1,2}, {0,0,0}, {100,200}}));
}

int main(int argc, char** argv) {
    test_merge_k_lists();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
