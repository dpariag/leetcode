// Leetcode: https://leetcode.com/problems/array-nesting/description/
// A zero-indexed array A of length N contains all integers from 0 to N-1.
// Find the length of the largest set S, where S[i] = {A[i], A[A[i]], A[A[A[i]]],...}

// Brute Force: Generate all possible subsets, then determine which ones satisfy the criteria.
// Better: Use an auxiliary array to determine if an element has been visited. Iterate A,
// following the "chain", until a visited element is hit. Track the longest chain. O(n) time/space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 36ms. Beats 50.0% of submissions, ties 12.50% of submissions
class Solution {
public:
    int arrayNesting(const std::vector<int>& nums) {
        std::vector<bool> visited(nums.size(), false);
        int max_size = 0;

        for (int i = 0; i < nums.size(); ++i) {
            int set_size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = nums[j];
                ++set_size;
            }
            max_size = std::max(max_size, set_size);
        }
        return max_size;
    }
};

void test_array_nesting() {
    Solution soln;

    assert(soln.arrayNesting({0,1,2,3}) == 1);
    assert(soln.arrayNesting({3,2,1,0}) == 2);
    assert(soln.arrayNesting({0,3,4,2,1}) == 4);
    assert(soln.arrayNesting({5,4,0,3,1,6,2}) == 4);
}

int main(int argc, char** argv) {
    test_array_nesting();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}