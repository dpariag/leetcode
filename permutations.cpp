// Leetcode: https://leetcode.com/problems/permutations/tabs/description
// Given a collection of distinct numbers, return all possible permutations.

// Better: Iterate the array, swapping A[i] with A[j] for j = i,..n. After each swap, recurse on 
// A[j...n]. O(n!) time and space.

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using Permutation = std::vector<int>;
using Permutations = std::vector<Permutation>;

int factorial(size_t n) {
    size_t result = 1;
    while (n > 1) { result *= n--;}
    return result;
}

// Accepted. 9ms. Beats 76.48% of submissions, ties 23.48% of submissions.
class Solution {
public:
    inline void permutations(Permutation& nums, int start, Permutations& perms) {
        if (start == nums.size() - 1) {
            perms.emplace_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            permutations(nums, start+1, perms);
            std::swap(nums[start], nums[i]); // undo last swap
        }
    }

    Permutations permute(std::vector<int>& nums) {
        Permutations perms;
        perms.reserve(factorial(nums.size()));
        permutations(nums, 0, perms);
        return perms;
    }
};

bool test_permutations(Permutation p, Permutations expected) {
    Solution soln;
    auto perms = soln.permute(p);
    std::sort(perms.begin(), perms.end());
    return (perms == expected);
}

void test_permutations() {
    assert(test_permutations({}, {}));
    assert(test_permutations({1}, {{1}}));
    assert(test_permutations({1,2}, {{1,2},{2,1}}));
    assert(test_permutations({1,2,3}, {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}));
}

int main(int argc, char** argv) {
    test_permutations();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
