// Leetcode: https://leetcode.com/problems/subsets/description/
// Given a set of distinct integers, return all possible subsets (the power set).

// Brute Force: Generate random sets of size 1,2,..,n until 2^n distinct sets generated. 
// Use a hash map to store distinct sets. O(2^n) time/extra space
// Better: Generate unique subsets using a bottom-up, iterative approach. O(2^n) time.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using Subset = std::vector<int>;
using Subsets = std::vector<Subset>;

// Accepted. 6ms. Beats 18.89% of submissions, ties 76.43% of submissions.
class Solution {
public:
    Subsets subsets(const std::vector<int>& nums) {
        Subsets result(1, Subset()); // empty set

        for (auto n : nums) {
            Subsets new_subsets;
            for (auto subset : result) {
                subset.emplace_back(n);
                new_subsets.emplace_back(subset);
            }
            result.insert(result.end(), new_subsets.begin(), new_subsets.end());
        }
        return result; 
    }
};

bool test_subsets(const std::vector<int>& nums, Subsets expected) {
    Solution soln;
    auto subsets = soln.subsets(nums);
    
    if (subsets.size() != expected.size()) { return false; }
    for (int i = 0; i < expected.size(); ++i) {
        std::sort(expected[i].begin(), expected[i].end());
        std::sort(subsets[i].begin(), subsets[i].end()); 
    }
    std::sort(expected.begin(), expected.end());
    std::sort(subsets.begin(), subsets.end());
    return subsets == expected;
}

void test_subsets() {
    assert(test_subsets({}, {{}}));
    assert(test_subsets({1}, {{},{1}}));
    assert(test_subsets({1,2}, {{},{1},{2},{1,2}}));
    assert(test_subsets({1,2,3}, {{},{1},{2},{3},{1,2},{1,3},{2,3},{1,2,3}}));
}

int main(int argc, char** argv) {
    test_subsets();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
