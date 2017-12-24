// Leetcode: https://leetcode.com/problems/zigzag-iterator/description/
// Given two 1d vectors, implement an iterator to return their elements alternately.

// Approach: Store each vector with it's current index. Use modulo arithmetic to cycle over vectors.
// Remove any vector whose elements have all been returned.

#include <vector>
#include <iostream>
#include <assert.h>

using Elems = std::vector<int>;

// Accepted. 19ms. Beats 34.05% of submissions, ties 52.43% of submissions.
class ZigzagIterator {
public:
    ZigzagIterator(Elems& v1, Elems& v2): m_cur(0) {
        if (!v1.empty()) m_data.emplace_back(v1, 0);
        if (!v2.empty()) m_data.emplace_back(v2, 0);
    }

    int next() {
        int& index = m_data[m_cur].index;
        int result = m_data[m_cur].elems[index];
        ++index;        
        if (index == m_data[m_cur].elems.size()) {
            m_data.erase(m_data.begin() + m_cur);
        }
        if (!m_data.empty()) {
            m_cur = (m_cur + 1) % m_data.size();
        }
        return result;
    }

    bool hasNext() {
        return !m_data.empty();
    }

private:
    int m_cur = 0;
    struct ElemIndex {
        Elems elems;
        int index = 0;
        ElemIndex(const Elems& e, int i): elems(e), index(i) {}
    };
    std::vector<ElemIndex> m_data;
};

bool test_iterator(Elems v1, Elems v2, Elems expected) {
    ZigzagIterator iter(v1, v2);

    for (int i = 0; i < expected.size(); ++i) {
        if (!iter.hasNext() || iter.next() != expected[i]) {
            return false;
        }
    }
    return !iter.hasNext();
}

void test_iterator() {
    assert(test_iterator({},{},{}));
    assert(test_iterator({1},{},{1}));
    assert(test_iterator({},{1},{1}));
    assert(test_iterator({1},{1},{1,1}));
    assert(test_iterator({},{4,5,6},{4,5,6}));
    assert(test_iterator({1},{4,5,6},{1,4,5,6}));
    assert(test_iterator({1,2},{4,5,6},{1,4,2,5,6}));
    assert(test_iterator({1,2,3},{4,5},{1,4,2,5,3}));
    assert(test_iterator({1,2,3},{4},{1,4,2,3}));
    assert(test_iterator({1,2,3},{},{1,2,3}));
    assert(test_iterator({1,2,3},{4,5,6},{1,4,2,5,3,6}));
}



int main(int argc, char** argv) {
    test_iterator();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
