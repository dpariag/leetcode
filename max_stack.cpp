// Leetcode: https://leetcode.com/problems/max-stack/description/
// Design a max stack that supports push, pop, top, peekMax and popMax.

// Brute Force: Use a traditional stack and do an O(n) scan for peekMax and popMax. 
// Better: Augment the stack with a multiset (tree) for efficient max finding
// All operations become O(logN) and the multiset consumes O(n) additional space.

#include <vector>
#include <set>
#include <iostream>
#include <assert.h>

// Accepted. 86ms. Beats 68.54% of submissions, ties 4.69% of submissions.
class MaxStack {
public:
    MaxStack() {}
    
    void push(int x) {
        m_stack.emplace_back(x, true);
        m_set.emplace(x, m_stack.size()-1);
    }
    
    int pop() {
        auto top = m_stack.back();  
        m_stack.pop_back();
        m_set.erase(SetEntry(top.val, m_stack.size()));
        purge();
        return top.val;
    }
    
    int top() {
        return m_stack.back().val;
    }
    
    int peekMax() {
        auto max_iter = --m_set.end();
        return max_iter->val;
    }
    
    int popMax() {
        auto max_iter = --m_set.end();
        auto val = max_iter->val;
        m_stack[max_iter->idx].valid = false;        
        purge();
        m_set.erase(SetEntry(max_iter->val, max_iter->idx));
        return val;
    }

private:
    int m_size = 0;

    struct StackEntry {
        int val = 0;
        int valid = false;
        StackEntry(int v, bool vld): val(v), valid(vld){} 
    };
    std::vector<StackEntry> m_stack;

    // Store stack entries in a multiset keyed by (entry, index) pairs
    struct SetEntry {
        int val = 0;    // Value
        int idx = 0;    // Index in m_stack
        SetEntry(int v, int i): val(v), idx(i) {}
        bool operator<(const SetEntry& other) const {
            return val < other.val || (val == other.val && idx < other.idx);
        }
    };
    std::multiset<SetEntry> m_set;

    void purge() {
        while (!m_stack.empty() && m_stack.back().valid == false) m_stack.pop_back(), --m_size;
    }
};

void test_max_stack_simple() {
    MaxStack stack;
    stack.push(5); 

    stack.push(1);
    
    stack.push(5);    

    assert(stack.top() == 5);
    assert(stack.popMax() == 5);
    assert(stack.top() == 1);
    assert(stack.peekMax() == 5);
    assert(stack.pop() == 1);
    assert(stack.top() == 5);
}

void test_max_stack_complex() {
    MaxStack stack;
    stack.push(4);
    assert(stack.top() == 4);
    stack.push(15);    
    assert(stack.top() == 15);
    assert(stack.peekMax() == 15);
    stack.push(15);
    stack.push(15);
    stack.push(2);
    stack.push(3);
    assert(stack.top() == 3);
    assert(stack.peekMax() == 15);
   
    assert(stack.popMax() == 15);
    assert(stack.peekMax() == 15);
    assert(stack.popMax() == 15);
    assert(stack.peekMax() == 15);
    assert(stack.top() == 3);
    assert(stack.pop() == 3);
    assert(stack.pop() == 2);
    assert(stack.pop() == 15);    
    assert(stack.peekMax() == 4);
    assert(stack.top() == 4);
}


void test_max_stack_complex_2() {
    MaxStack stack;
    stack.push(74);
    assert(stack.popMax() == 74);
    stack.push(89);
    stack.push(67);
   
    assert(stack.popMax() == 89);
    assert(stack.pop() == 67);
   
    return;
    stack.push(61);
    stack.push(-77);
   
    assert(stack.peekMax() == 61);
    assert(stack.popMax() == 61);
    stack.push(81);
    assert(stack.pop() == 81);
    stack.push(-71);
    stack.push(32);
}

int main(int argc, char** argv) {
    test_max_stack_simple();
    test_max_stack_complex();
    test_max_stack_complex_2();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
