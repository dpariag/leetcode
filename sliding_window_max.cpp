// Leetcode: https://leetcode.com/problems/sliding-window-maximum/#/description
// Given an array nums, generate a sliding window (of size k,  1 <= k <= nums.size()) 
// moving left to right across the array one element at a time. 
// Return a vector containing the max. of each window instance.

// Brute Force: Generate all windows, and scan each for it's max. O(n*k) time.
// Better: Use a MaxQueue to track the max of the sliding window. The MaxQueue returns max() and pop()
// in O(1) time, and implements push() in amortized O(1) time. Overall O(n) time and O(k) space

#include <queue>
#include <iostream>
#include <assert.h>

template <typename T>
class MaxQueue {
public:
    inline const T& max() const {
        return m_max_elems.front();
    }

    inline void push(const T& elem) {
        m_elems.push(elem);
        while (!m_max_elems.empty() && m_max_elems.back() < elem) { m_max_elems.pop_back(); }
        m_max_elems.push_back(elem);
    }

    inline void pop() {
        if (m_max_elems.front() == m_elems.front()) {
            m_max_elems.pop_front();
        }
        m_elems.pop();
    }
    
private:                
    std::queue<T> m_elems;
    std::deque<T> m_max_elems;
};

// Accepted. 69ms. Beats 64.99% of submissions, ties 16.25% of submissions.
class Solution {
public:
    std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
        std::vector<int> window_max;
        MaxQueue<int> max_queue;

        if (nums.empty() || k == 0) { return window_max; } 
        for (int i = 0; i < nums.size(); ++i) {
            if (i >= k) {
                window_max.emplace_back(max_queue.max());
                max_queue.pop();
            }
            max_queue.push(nums[i]);
        }
        window_max.emplace_back(max_queue.max());
        return window_max;
    }
};

using Values = std::vector<int>;
void test_max_sliding_window() {
    Solution soln;
    assert(soln.maxSlidingWindow({2,2,2,2}, 4) == Values({2}));
    assert(soln.maxSlidingWindow({2,2,2,2}, 2) == Values({2,2,2}));
    assert(soln.maxSlidingWindow({8,7,6,5}, 2) == Values({8,7,6}));
    assert(soln.maxSlidingWindow({2,8,19,1,0,22,4,1,6}, 1) == Values({2,8,19,1,0,22,4,1,6}));
    assert(soln.maxSlidingWindow({2,8,19,1,0,22,4,1,6}, 2) == Values({8,19,19,1,22,22,4,6}));
    assert(soln.maxSlidingWindow({2,8,19,1,0,22,4,1,6}, 3) == Values({19,19,19,22,22,22,6}));
}

int main(int argc, char** argv) {
    test_max_sliding_window();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
