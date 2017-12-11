// Leetcode: https://leetcode.com/problems/contains-duplicate-iii/description/
// Given an integer array, determine if i and j exist such that i != j,
// abs(nums[i] - nums[j]) <= t and abs(i - j) <= k.

// Brute Force: Generate all pairs of indices, check if each pair satisfies the constraints. O(n^2)
// Better: Use a multiset (BST) to store a sliding window of size k over the array.
// New items are inserted and distance to their nearest neigbours are checked. O(n*logk)

#include <vector>
#include <set>
#include <iostream>
#include <assert.h>

// Accepted. 16ms. Beats 48.42% of submissions, ties 33% of submissions.
class Solution {
public:
    bool containsNearbyAlmostDuplicate(const std::vector<int>& nums, int k, int t) {
        if (k == 0) { return false; }
        std::multiset<int> window;

        for (int i = 0; i < nums.size(); ++i) {
            if (window.size() > k) {
                window.erase(window.find(nums[i-k-1]));
            }
            auto iter = window.emplace(nums[i]);
            auto next = iter, prev = iter;
            if (++next != window.end() && std::abs(int64_t(*iter) - int64_t(*next)) <= t) {
                return true;
            }
            if (iter != window.begin() && std::abs(int64_t(*iter) - int64_t(*(--prev))) <= t) {
                return true;
            }
        }
        return false;
    }
};

void test_contains_duplicate() {
    Solution soln;

    assert(soln.containsNearbyAlmostDuplicate({1,3,1},1,1) == false);
    assert(soln.containsNearbyAlmostDuplicate({1,3,2,5},2,1) == true);
    assert(soln.containsNearbyAlmostDuplicate({11},1,11) == false);
    assert(soln.containsNearbyAlmostDuplicate({11,11},1,11) == true);
    assert(soln.containsNearbyAlmostDuplicate({-1, 2147483647},1,2147483647) == false);
}

int main(int argc, char** argv) {
    test_contains_duplicate();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
