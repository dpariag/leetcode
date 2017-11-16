// Leetcode: https://leetcode.com/problems/permutations/tabs/description
// Given a collection of distinct numbers, return all possible permutations.

// Brute Force: Generate all permutations, and use a hash map to filter out duplicates. 
// O(n!) time and space.
// Better: Generate permutations using the same approach shown in permutations.cpp
// However, only swap and recurse if the swap would generate a new permutation. 

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Permutation = std::vector<int>;
using Permutations = std::vector<Permutation>;

int factorial(size_t n) {
    size_t result = 1;
    while (n > 1) { result *= n--;}
    return result;
}

// Accepted. 36ms. Beats 17.71% of submissions, ties 4.28% of submissions.
class Solution {
public:
    void permutations(Permutation& nums, int start, Permutations& perms) {
        if (start == nums.size() - 1) {
            perms.emplace_back(nums);
        }

        std::unordered_set<int> used;
        for (int i = start; i < nums.size(); ++i) {
            if (used.count(nums[i]) == 0) {
                std::swap(nums[start], nums[i]);
                permutations(nums, start+1, perms);
                std::swap(nums[start], nums[i]); // undo last swap
                used.emplace(nums[i]);
            }
        }
    }

    Permutations permuteUnique(std::vector<int>& nums) {
        Permutations perms;
        perms.reserve(factorial(nums.size()));
        std::sort(nums.begin(), nums.end());
        permutations(nums, 0, perms);
        return perms;
    }
};


bool test_permutations(Permutation p, Permutations expected) {
    Solution soln;
    auto perms = soln.permuteUnique(p);
    std::sort(perms.begin(), perms.end());
    return (perms == expected);
}

void test_permutations() {
    assert(test_permutations({}, {}));
    assert(test_permutations({1}, {{1}}));
    assert(test_permutations({1,2}, {{1,2},{2,1}}));
    assert(test_permutations({1,2,3}, {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}));
    assert(test_permutations({1,1,2}, {{1,1,2},{1,2,1},{2,1,1}}));
    assert(test_permutations({2,2,1,1}, 
                {{1,1,2,2},{1,2,1,2},{1,2,2,1}, {2,1,1,2}, {2,1,2,1},{2,2,1,1}}));
}

int main(int argc, char** argv) {
    test_permutations();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
