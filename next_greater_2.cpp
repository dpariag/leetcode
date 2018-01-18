// Leetcode: https://leetcode.com/problems/next-greater-element-ii/description/
// Given a circular array, find the first greater number to the right of each element
// (incl. wrapping). Output -1 if none exists.

// Brute Force:
// Better:

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>

// Accepted. 110ms. Beats 63.55% of submissions, ties < 1% of submissions.
class Solution {
public:
    std::vector<int> nextGreaterElements(const std::vector<int>& nums) {
        std::vector<int> result(nums.size(), -1);
        if (nums.empty()) { return result; }

        std::stack<int> indices; // indices of elems whose next greater is unknown
        indices.emplace(0);
        int i = 1 % nums.size();
        while (!indices.empty() && indices.top() != i) {
            while (!indices.empty() && nums[i] > nums[indices.top()]) {
                result[indices.top()] = nums[i];
                indices.pop();
            }
            if (!indices.empty() && indices.top() == i) { break; }
            if (indices.empty() || i > indices.top()) { indices.emplace(i); }
            i = (i + 1) % nums.size();
        }
        return result;
    }
};

using Numbers = std::vector<int>;
bool test_next_greater(Numbers nums, Numbers expected) {
    Solution soln;
    return soln.nextGreaterElements(nums) == expected;
}

void test_next_greater() {
    assert(test_next_greater({}, {}));
    assert(test_next_greater({5}, {-1}));
    assert(test_next_greater({1,2,3}, {2,3,-1}));
    assert(test_next_greater({3,2,1}, {-1,3,3}));
    assert(test_next_greater({1,2,4,0,-1,6,1,7,3}, {2,4,6,6,6,7,7,-1,4}));
    assert(test_next_greater({2,2,2,2}, {-1,-1,-1,-1}));
    assert(test_next_greater({2,2,4,2}, {4,4,-1,4}));
}

int main(int argc, char** argv) {
    test_next_greater();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
