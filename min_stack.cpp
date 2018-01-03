// Leetcode: https://leetcode.com/problems/min-stack/description/
// Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

// Brute Force: Store items in a vector, iterate to find min in O(n) time.
// Better: Store the current min with each item in the stack. O(1) time and O(n) space.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 26ms. Beats 64.98% of submissions, ties 26.60% of submissions.
class MinStack {
public:
    MinStack() {}

    void push(int x) {
        auto cur_min = m_stack.empty() ? std::numeric_limits<int>::max() : m_stack.back().min;
        m_stack.emplace_back(x, std::min(cur_min, x));
    }

    void pop() {
        m_stack.pop_back();
    }

    int top() {
        return m_stack.back().val;
    }

    int getMin() {
        return m_stack.back().min;
    }

private:
    struct Item {
        int val;
        int min;
        Item(int v, int m): val(v), min(m) {}
    };
    std::vector<Item> m_stack;
};


int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
