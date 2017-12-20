// Leetcode: https://leetcode.com/problems/insert-delete-getrandom-o1/description/
// Design a data structure that supports all following operations in average O(1) time.
//  insert(val): Inserts an item val to the set if not already present.
//  remove(val): Removes an item val from the set if present.
//  getRandom(): Returns a random element from current set of elements.

// Approach: Use a hash map and a vector together to provide the required runtimes.

#include <vector>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 52ms. Beats 41.80% of submissions, ties 13.26% of submissions.
class RandomizedSet {
public:
    RandomizedSet(): m_indices(1000) {
        m_items.reserve(1000);
    }
   
    /* Inserts a value. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto found = m_indices.find(val);
        if (found != m_indices.end()) { return false; }

        m_items.emplace_back(val);
        m_indices[val] = m_items.size() - 1;
        return true; 
    }
   
    /* Removes a value. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto found = m_indices.find(val);
        if (found == m_indices.end()) { return false; }
        
        auto index = found->second; 
        std::swap(m_items[index], m_items.back());
        m_items.pop_back();
        m_indices[m_items[index]] = index;
        m_indices.erase(found);
        return true;
    }
   
    /** Get a random element from the set. */
    int getRandom() {
        auto index = std::rand() % m_items.size(); // assumes non-empty
        return m_items[index]; 
    }

private:
    using Items = std::vector<int>;
    using Indices = std::unordered_map<int, int>;   // Map an item to it's index in Items

    Indices m_indices;
    Items m_items;
};

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
