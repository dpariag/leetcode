// Leetcode: https://leetcode.com/problems/132-pattern/description/
// Given an integer array, determine if a triple (A[i], A[j], A[k]) exists such that i < j < k and 
// and A[i] < A[k] < A[j].

// Brute Force: Generate all triples, and check each against constraints. O(n^3) time.
// Better: Scan right to left using a stack to track max values seen so far.
// Stop if the stack is non-empty (max found), a middle has been found, and A[i] <= middle.

#include <vector>
#include <limits>
#include <iostream>
#include <assert.h>

// Accepted. 26ms. Beats 71.56% of submissions.
class Solution {
public:
    bool find132pattern(const std::vector<int>& nums) {
        if (nums.size() < 3) { return false; }
        std::vector<int> stack;
        stack.reserve(nums.size());

        int middle = std::numeric_limits<int>::min();
        for (int i = nums.size()-1; i >= 0; --i) {

            while(!stack.empty() && stack.back() < nums[i]) {                
                middle = std::max(middle, stack.back());
                stack.pop_back();
            }
            if (nums[i] < middle && !stack.empty()) {
                return true;
            }
            stack.emplace_back(nums[i]);
        }
        return false;
    }
};

void test_132_pattern() {
    Solution soln;

    assert(soln.find132pattern({-2,1,-1}) == true);
    assert(soln.find132pattern({-2,1,2,-2,1,2}) == true);
    assert(soln.find132pattern({3,5,0,3,4}) == true);
    assert(soln.find132pattern({3,5,0,3,2}) == true);
    assert(soln.find132pattern({3,1,4,2}) == true);
    assert(soln.find132pattern({10,1,2,3,4,2}) == true);
    assert(soln.find132pattern({10,1,2,3,4,5}) == false);
    assert(soln.find132pattern({-1,3,2,0}) == true);
    assert(soln.find132pattern({1,2,3,4}) == false);    
    assert(soln.find132pattern({1,0,1,-4,-3}) == false);
}

int main(int argc, char** argv) {
    test_132_pattern();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
