// Leetcode: https://leetcode.com/problems/climbing-stairs/description/
// Calculate how many ways you can climb up n steps if you can take 1 or 2 steps at a time.

// Brute Force: Recursively evaluate number of ways to climb (n-1) + (n-2) steps. O(2^n) time.
// Better: Build solution bottom up using: num_steps(n) = nums_steps(n-1) + nums_steps(n-2). 
// O(n) time and O(1) space

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 93.77% of submissions.
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) { return n; }
        int num_steps = 0, one_back = 2, two_back = 1, cur_step = 2;

        while (cur_step <  n) {
            num_steps = (one_back + two_back);
            two_back = one_back;
            one_back = num_steps;
            ++cur_step;
        }
        return num_steps;
    }
};

void test_climb_stairs() {
    Solution soln;
    assert(soln.climbStairs(1) == 1);
    assert(soln.climbStairs(2) == 2);
    assert(soln.climbStairs(3) == 3);
    assert(soln.climbStairs(4) == 5);    
    assert(soln.climbStairs(5) == 8);
}

int main(int argc, char** argv) {
    test_climb_stairs();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}