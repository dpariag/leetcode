// Leetcode: https://leetcode.com/problems/find-median-from-data-stream/description/

// Brute Force: Maintain a sorted array. O(n) insert and O(1) median.
// Better: Use two heaps. O(logn) insert and O(1) median. 

#include <queue>
#include <iostream>
#include <assert.h>

// Accepted. 157ms. Beats 58.97% of submissions, ties < 1% of submissions.
class MedianFinder {
public:
    MedianFinder() {}

    void addNum(int num) {
        // Insert the new value
        double value(num); 
        if (value <= m_median || m_size == 0) {
            m_smaller.emplace(num);
        } else {
            m_larger.emplace(num);
        }

        // Rebalance heaps if needed
        if (m_smaller.size() > m_larger.size() + 1) {
            m_larger.emplace(m_smaller.top());
            m_smaller.pop();
        }

        if (m_larger.size() > m_smaller.size() + 1) {
            m_smaller.emplace(m_larger.top());
            m_larger.pop();
        }

        // Re-calculate the median
        if (m_smaller.size() == m_larger.size()) {
            m_median = (double(m_smaller.top()) + double(m_larger.top())) / 2.0;
        } else {
            m_median = (m_smaller.size() > m_larger.size()) ? m_smaller.top() : m_larger.top();
        }
        ++m_size;
    }

    double findMedian() {
        return m_median;
    }
private:
    using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<int>>;
    using MaxHeap = std::priority_queue<int, std::vector<int>, std::less<int>>;

    MaxHeap m_smaller;
    MinHeap m_larger;
    double m_median;
    size_t m_size = 0;
};

void test_median_finder() {
    MedianFinder m;

    m.addNum(2);
    assert(m.findMedian() == 2.0);
    m.addNum(4);
    assert(m.findMedian() == 3.0);
    m.addNum(3);
    assert(m.findMedian() == 3.0);
    m.addNum(5);
    assert(m.findMedian() == 3.5);
}

int main(int argc, char** argv) {
    test_median_finder();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
