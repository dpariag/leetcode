// Leetcode: https://leetcode.com/problems/flatten-2d-vector/description/
// Implement an iterator to flatten a 2d vector. 
// For bonus points, implement the iterator using C++ iterators.

// Approach: Using C++ iterators only... Maintain a row iterator and a column iterator.
// On initialization, advance the iterators to the first item in the first non-empty row.
// After each value returned, advance the column iterator, and possibly also the row iterator.
// Handle special cases (empty 2D-vectors, empty rows) carefully.

#include <vector>
#include <iostream>
#include <assert.h>

using Row = std::vector<int>;
using Table = std::vector<Row>;

// Accepted. 15ms. Beats 42.53% of submissions, ties 1.55% of submissions.
class Vector2D {
public:
    Vector2D(Table& t): row_iter(t.begin()), m_table(t) {
        if (row_iter != m_table.end()) {
            col_iter = row_iter->begin();
        }
        advance();
    }

    // Assumes hasNext() returns true
    int next() {
        auto value = *col_iter;
        ++col_iter;
        advance();
        return value;
    }

    bool hasNext() {
        return (row_iter != m_table.end() && col_iter != row_iter->end());
    }

private:
    void advance() {
        while (row_iter != m_table.end() && col_iter == row_iter->end()) {
            ++row_iter;
            col_iter = row_iter->begin();
        }
    }

    Table::iterator row_iter;
    Row::iterator col_iter;
    const Table& m_table;
};

bool test_vector_2d(Table t, Row expected) {
    Vector2D v(t);

    for (int i = 0; i < expected.size(); ++i) {
        if (!v.hasNext() || v.next() != expected[i]) { return false; }
    }
    return !v.hasNext();
}

void test_vector_2d() {

    assert(test_vector_2d({{}}, {}));
    assert(test_vector_2d({{},{},{}}, {}));
    assert(test_vector_2d({{2}}, {2}));
    assert(test_vector_2d({{1,2,3},{4,5,6}}, {1,2,3,4,5,6}));
    assert(test_vector_2d({{1},{2,5,6}}, {1,2,5,6}));
    assert(test_vector_2d({{2,5,6}}, {2,5,6}));
    assert(test_vector_2d({{2,5,6},{},{},{7}}, {2,5,6,7}));
}

int main(int argc, char** argv) {
    test_vector_2d();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}