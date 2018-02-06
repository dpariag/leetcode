// Leetcode: https://leetcode.com/problems/flatten-nested-list-iterator/description/
// Given a nested list of integers, implement an iterator to flatten it.
// Each element is either an integer, or a list whose elements may also be integers or other lists

// Approach: Use a stack<NestedInteger> to hold the next nested integer to return.
// If the top NestedInteger is a list, push it's contents (in reverse) onto the stack. Repeat

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger> &getList() const;
};
 
// Accepted. 16ms. Beats 61.87% of submissions, ties 35.97% of submissions.
class NestedIterator {
public:
    NestedIterator(std::vector<NestedInteger> &nestedList) {
        push_list(nestedList);
        get_next();
    }

    int next() {
        auto result = m_stack.top().getInteger();
        m_stack.pop();
        get_next();
        return result;
    }

    bool hasNext() {
        return !m_stack.empty();
    }

private:
    inline void push_list(const std::vector<NestedInteger>& list) {
        for (int i = list.size()-1; i >= 0; --i) {
            m_stack.emplace(list[i]);
        } 
    }

    inline void get_next() {
        while (!m_stack.empty() && !m_stack.top().isInteger()) {
            auto list = m_stack.top().getList();
            m_stack.pop();
            push_list(list);
        }
    }

    std::stack<NestedInteger> m_stack;
};

void test_nested_iterator() {
}

int main(int argc, char** argv) {
    test_nested_iterator();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
