// Leetcode: https://leetcode.com/problems/perfect-squares/ 
// Given n > 0, find the least number of perfect squares (e.g., 1, 4, 9, 16, ...) which sum to n.
// Example: Given n = 12, return 3 (12 = 4 + 4 + 4); given n = 13, return 2 (13 = 4 + 9).

// Brute Force: Recursive decomposition of integer, using each 
// Better:

#include <vector>
#include <iostream>
#include <assert.h>
#include <unordered_map>

using Squares = std::vector<int>;

struct CacheEntry {
    int sum = 0;
    int largest_square = 0;
    
    CacheEntry(int s, int l) : sum(s), largest_square(l) {}
    bool operator==(const CacheEntry& other) const {
        return sum == other.sum && largest_square == other.largest_square;
    }
};

struct Hash {
    size_t operator()(const CacheEntry& c) const {
        return c.sum * 19 + c.largest_square * 13;
    }
};

using Cache = std::unordered_map<CacheEntry, int, Hash>;

class Solution {
public:
    int numSquares(int n) {
        Cache cache;
        int to_square = m_squares.size() + 1;
        int square = to_square * to_square;
        while (square <= n) {
            m_squares.emplace_back(square);
            to_square = m_squares.size() + 1;
            square = to_square * to_square; 
        }
        return min_num_squares(cache, n, int(m_squares.size()) - 1);
    }

    int min_num_squares(Cache& cache, int n, int index) {
        if (n == 0) { return 0; }
       
        auto found = cache.find(CacheEntry(n, m_squares[index]));
        if (found != cache.end()) {
            return found->second;
        }

        int min_ways = std::numeric_limits<int>::max();
        for (int i = index; i >= 0; --i) {
            if (m_squares[i] <= n) {
                int ways = 1 + min_num_squares(cache, n - m_squares[i], i);
                min_ways = std::min(min_ways, ways);
            }
        }
        cache.emplace(CacheEntry(n, m_squares[index]), min_ways);
        return min_ways;
    }

private: 
    static Squares m_squares;
};

Squares Solution::m_squares = Squares(1,1);

void test_num_squares() {
    Solution soln;
    assert(soln.numSquares(1) == 1);
    assert(soln.numSquares(9) == 1);
    assert(soln.numSquares(19) == 3); // 19 = 9 + 9 + 1
    assert(soln.numSquares(20) == 2); // 20 = 16 + 4 
    assert(soln.numSquares(10) == 2); // 10 = 9 + 1
    assert(soln.numSquares(22) == 3); // 22 = 9 + 9 + 4
    assert(soln.numSquares(35) == 3); // 35 = 25 + 9 + 1
    //assert(soln.numSquares(9732) == 4); // 9732 = (98*98) + (11*11) +  
}

int main(int argc, char** argv) {
    test_num_squares();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
