// Leetcode: https://leetcode.com/problems/sliding-window-median/description/
// Given an array nums, and a sliding window of size k, return an array which contains the median 
// of each sliding window position.

// Brute Force: Sort each sliding window to find the median. O((k*logk)*(n-k))
// Better: Use two BSTs to partition the window into elements smaller than the median, and elements
// larger than the median. O(logk*(n-k)) time.

#include <vector>
#include <set>
#include <iostream>
#include <assert.h>

class MedianFinder {
public:
    // Assumes that the MedianFinder is non-empty
    inline double get_median() const {
        if (m_smaller.size() > m_larger.size()) {
            return *(--m_smaller.end());
        } else if (m_smaller.size() < m_larger.size()) {
            return *(m_larger.begin());
        } 
        // equal size
        return (double(*(--m_smaller.end())) + double(*(m_larger.begin()))) / 2.0;
    }

    inline void insert(int value) {
        if (m_smaller.empty() && m_larger.empty()) {
            m_smaller.emplace(value);
        } else {
            value <= int(get_median()) ? m_smaller.emplace(value) : m_larger.emplace(value);
        }
        rebalance();
    }

    inline void remove(int value) {
        auto found = m_smaller.find(value);
        if (found != m_smaller.end()) {
            m_smaller.erase(found);
        } else {
            found = m_larger.find(value);
            m_larger.erase(found);
        }
        rebalance();
    }

    inline size_t size() const {
        return m_smaller.size() + m_larger.size();
    }

    inline void rebalance() {
        int num_smaller = m_smaller.size();
        int num_larger = m_larger.size();
        if (num_smaller - num_larger > 1) {
            auto max_iter = --m_smaller.end();
            m_larger.emplace(*max_iter);
            m_smaller.erase(max_iter);
        } else if (num_larger - num_smaller > 1) {
            auto min_iter = m_larger.begin();
            m_smaller.emplace(*min_iter);
            m_larger.erase(min_iter);
        }
    }
    
    void print() {
        std::cout << "{";
        for (auto value : m_smaller) {
            std::cout << value << ",";
        }
        std::cout << "} ";
        
        std::cout << "{";
        for (auto value : m_larger) {
            std::cout << value << ",";
        }
        std::cout << "} ";
    }

private:
    std::multiset<int> m_smaller;    // elements <= the median
    std::multiset<int> m_larger;     // elements >= the median

    void erase(std::multiset<int>& set, int value) {
        auto found = set.find(value);
        assert(found != set.end());
        if (found != set.end()) { set.erase(found); }
    }

};

// Accepted. 65ms. Beats 83.72% of submissions, ties ~5% of submissions.
class Solution {
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        MedianFinder median_finder;
        std::vector<double> medians;
        
        for(int i = 0; i < nums.size(); ++i) {
            if (median_finder.size() < k) {
                median_finder.insert(nums[i]);
            } else {
                median_finder.remove(nums[i-k]);
                median_finder.insert(nums[i]);
            }
            if (median_finder.size() >= k) {
                medians.emplace_back(median_finder.get_median());
            }
        }
        return medians; 
    }
};

bool test_medians(std::vector<int> values, int k, std::vector<double> expected) {
    Solution soln;
    auto medians = soln.medianSlidingWindow(values, k);
    return medians == expected;
}

void test_medians() {
    assert(test_medians({1}, 1, {1.0}));
    assert(test_medians({1,2}, 1, {1.0,2.0}));
    assert(test_medians({3,1,2}, 2, {2.0,1.5}));
    assert(test_medians({1,3,-1,-3,5,3,6,7}, 3, {1.0,-1.0,-1.0,3.0,5.0,6.0}));
}

int main(int argc, char** argv) {
    test_medians();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
