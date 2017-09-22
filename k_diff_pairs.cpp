// Leetcode: https://leetcode.com/problems/k-diff-pairs-in-an-array/description/
// Given an integer array and an integer k, find the number of pairs (i,j) where abs(i-j) == k. 

// Brute Force: Generate all pairs, and count those with difference k. O(n^2) time.
// Better: Use a hash map and a hash set to track pairs recorded, and elems processed respectively.
// O(n) time and space. 

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 36ms. Beats 50.70% of submissions, ties 17.30% of submissions.
class Solution {
public:
    int findPairs(const std::vector<int>& nums, int k) {
        if (k < 0) { return 0; } // abs difference must be +ve
        std::unordered_set<int> elems;
        std::unordered_map<int,int> pairs; // map smaller -> larger
        int num_pairs = 0;

        for (auto n : nums) {
            // Look for (n, n-k)
            if (elems.count(n-k) > 0 && pairs.count(n-k) == 0) {
                ++num_pairs;
                pairs.emplace(n-k, n);
            }
            // Look for (n, n+k)
            if (elems.count(n+k) > 0 && pairs.count(n) == 0) {
                ++num_pairs;
                pairs.emplace(n, n+k);
            }
            elems.emplace(n); // remember n
        }
        return num_pairs;
    }
};

void test_find_pairs() {
    Solution soln;

    assert(soln.findPairs({}, 5) == 0);
    assert(soln.findPairs({1,2,3,4,5}, 1) == 4);
    assert(soln.findPairs({1,3,1,5,4}, 0) == 1);
    assert(soln.findPairs({3,1,4,1,5}, 2) == 2);
    assert(soln.findPairs({3,3,3,3,3}, 1) == 0);
    assert(soln.findPairs({3,3,3,3,3}, 0) == 1);
    assert(soln.findPairs({6,3,5,7,2,3,3,8,2,4}, 2) == 5);
}

int main(int argc, char** argv) {
    test_find_pairs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
