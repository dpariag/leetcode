// Leetcode: https://leetcode.com/problems/number-of-islands-ii/description/
// Given an m*n grid filled with zeroes, we sequentially flip certain positions to 1's.
// A 1 is "connected" to any 1s above, below, left or right of it.
// Return the number of "islands" of 1s after each 1 is added.

// Brute Force: Track each set using an unordered_set, and merge adjacent sets in O(n) time.
// Better: Track and merge sets using the Union-Find data structure. It tracks sets using
// an inverted tree structure represented in an array. See union_find.h for details.
// Set merge is now O(logN) time.

#include <vector>
#include <iostream>
#include <assert.h>
#include "union_find.h"

using Position = std::pair<int,int>;
using Positions = std::vector<Position>;

// Accepted. 89ms. Beats 98.14% of submissions, ties 1.67% of submissions.
class Solution {
public:
    std::vector<int> numIslands2(int m, int n, Positions& positions) {
        std::vector<int> counts;
        UnionFind uf(m*n); // Population is items {0,1,2,...,m*n-1}
       
        for (auto& pos : positions) {
            int cur = (pos.first*n) + pos.second;
            uf.add(cur);
            
            // Merge with any land to the left 
            int left = cur - 1;
            if ((cur % n) != 0 && uf.find(left) != -1) { uf.merge(cur, left); }

            // Merge with any land to the right
            int right = cur + 1;
            if ((cur % n) != n-1 && uf.find(right) != -1) { uf.merge(cur, right); }

            // Merge with any land above
            int above = cur - n;
            if (above >= 0 && uf.find(above) != -1) { uf.merge(cur, above); }

            // Merge with any land below
            int below = cur + n;
            if (below < (m*n) && uf.find(below) != -1) { uf.merge(cur, below); }
            
            counts.emplace_back(uf.count());
        } 
        return counts;
    }
};

bool test_num_islands(int m, int n, Positions positions, std::vector<int> expected) {
    Solution soln;
    return soln.numIslands2(m, n, positions) == expected;
}

void test_num_islands() {
    assert(test_num_islands(3,3, {{0,1},{1,2},{2,1},{1,0},{0,2},{0,0}, {1,1}}, {1,2,3,4,3,2,1}));
    assert(test_num_islands(1,4, {{0,0},{0,3},{0,2},{0,1}}, {1,2,2,1}));
    assert(test_num_islands(3,3, {{0,0},{0,1},{1,2},{2,1}}, {1,1,2,3}));
    assert(test_num_islands(4,4, {{0,1},{2,1},{1,2},{1,0},{1,1}}, {1,2,3,4,1}));
}

int main(int argc, char** argv) {
    test_num_islands();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}