#include <vector>
#include <iostream>
#include <assert.h>

class UnionFind {
public:
    UnionFind(int n): m_set(n) {}

    void add(int i) {
        if (m_set[i].parent == -1) {
            m_set[i].parent = i;
            m_set[i].count = 1;
            ++m_count;
        }
    }

    int find(int i) {
        int result = -1;
        while (m_set[i].parent != -1) {
            result = m_set[i].parent;
            if (result == i) { break; }
            i = result;
        }
        return result;
    }

    int count() const { return m_count; }

    void merge(int i, int j) {
        int set_i = find(i);
        int set_j = find(j);
        if (set_i == -1 || set_j == -1 || set_i == set_j) { return; }

        if (m_set[set_i].count < m_set[set_j].count) {
            m_set[set_i].parent = m_set[set_j].parent;
            m_set[set_j].count += m_set[set_i].count;
        } else {
            m_set[set_j].parent = m_set[set_i].parent;
            m_set[set_i].count += m_set[set_j].count;
        }
        --m_count;
    }

private:
    struct Elem {
        int count = 0;
        int parent = -1;
    };
    int m_count = 0;
    std::vector<Elem> m_set;
};
