// Leetcode: 
// Design and implement a Least Recently Used (LRU) cache. It should support the following operations:
// get(key) - If the key (assumed +ve) exists, return the associated value, otherwise return -1.
// put(key, value) - Set or insert the value if the key is not already present. If the cache is at
// capacity, invalidate the least recently used item before inserting the new item.

// Brute Force:
// Better:

#include <list>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 89ms. Beats 80.89% of submissions, ties 8.39% of submissions.
class LRUCache {
public:
    LRUCache(int capacity): m_capacity(capacity), m_cache(2*capacity) {}

    int get(int key) {
        auto found = m_cache.find(key);
        if (found != m_cache.end()) {
            m_lru_order.push_front(key);
            m_lru_order.erase(found->second.pos);
            found->second.pos = m_lru_order.cbegin();
            return found->second.value;
        }
        return -1;
    }

    inline void evict() {
        auto to_evict = m_lru_order.back();
        m_lru_order.pop_back();
        m_cache.erase(to_evict);
    }

    void put(int key, int value) {
        auto found = m_cache.find(key);
        if (found == m_cache.end()) {
            // Didn't find it, check if we should evict
            if (m_cache.size() == m_capacity) { evict(); }
            m_lru_order.push_front(key);
            m_cache.insert(std::make_pair(key, CacheItem(value, m_lru_order.cbegin())));
        } else {
            // Did find it
            m_lru_order.push_front(key);
            m_lru_order.erase(found->second.pos);
            found->second.pos = m_lru_order.cbegin();
            found->second.value = value;
        }
    }

private:
    int m_capacity;
    using LRUOrder = std::list<int>;
    using Position = LRUOrder::const_iterator;
    struct CacheItem {
        int value;
        Position pos;
        CacheItem(int v, const Position& p) : value(v), pos(p) {}
    };
    LRUOrder m_lru_order;
    std::unordered_map<int,CacheItem> m_cache;
};

void test_lru_cache() {
    LRUCache cache(2);
    cache.put(1,1);
    cache.put(2,2);
    assert(cache.get(1) == 1);
    cache.put(3,3);
    assert(cache.get(2) == -1);
    cache.put(4,4);
    assert(cache.get(1) == -1);
    assert(cache.get(3) == 3);
    assert(cache.get(4) == 4);
}

int main(int argc, char** argv) {
    test_lru_cache();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
