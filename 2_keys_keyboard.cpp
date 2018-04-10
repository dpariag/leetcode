// Leetcode: https://leetcode.com/problems/2-keys-keyboard/description/
// Determine the min. number of steps to produce N 'A's, starting with one 'A' and if allowed to:
// 1) Copy all current text 2) Paste all copied text.

// Approach: Realize that the problem boils down to finding the largest factor of N.
// Can be done recursively, or using dynamic programming (DP is slower)

#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 5ms. Beats 90.34% of submissions.
class Solution {
public:
    int minSteps_DP(int n) {
        std::vector<int> steps(n+1, std::numeric_limits<int>::max());
        steps[0] = 0, steps[1] = 0;

        for (int i = 2; i <= n; ++i) {
            for (int divisor = (i/2); divisor >= 1; --divisor) {
                if (i % divisor == 0) {                    
                    int dividend = i / divisor;
                    steps[i] = std::min(steps[i], (steps[divisor]) + dividend);
                    break;
                }
            }
        }
        return steps.back();
    }

    int minSteps(int n) {
        if (n == 1) { return 0; }

        for (int divisor = (n/2); divisor > 1; --divisor) {
            if (n % divisor == 0) {
                int dividend = (n/divisor);
                auto result = minSteps(divisor) + dividend;
                return result;
            }
        }
        return n;
    }
};

void test_min_steps() {
    Solution soln;
    
    assert(soln.minSteps(1) == 0);
    assert(soln.minSteps(2) == 2);
    assert(soln.minSteps(3) == 3);
    assert(soln.minSteps(4) == 4);
    assert(soln.minSteps(5) == 5);
    assert(soln.minSteps(6) == 5);
    assert(soln.minSteps(7) == 7);
    assert(soln.minSteps(8) == 6);
    assert(soln.minSteps(9) == 6);
    assert(soln.minSteps(10) == 7);
    assert(soln.minSteps(18) == 8);
}
 
int main(int argc, char** argv) {
    test_min_steps();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
