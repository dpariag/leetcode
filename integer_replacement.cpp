// Leetcode: https://leetcode.com/problems/integer-replacement/description/
// Given a positive integer n, you can replace it by n/2 if it is even, or replace it by n+1 or n-1 
// if it is odd. What is the minimum number of replacements to arrive at 1? 

// Brute Force: Divide by 2 while even, try both options when odd and return the smaller one.
// Better: Memoize to avoid repeated work when trying n+1/n-1. Pre-populate cache with powers of 2.

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Cache = std::unordered_map<int,int>; // N --> # of replacements required

// Accepted. 3ms. Beats 21.47% of submissions, ties 59.89% of submissions
class Solution {
public:
    int min_replacements(int n, Cache& cache) {
        // Check for a cached solution
        auto found = cache.find(n);
        if (found != cache.end()) { return found->second; }

        // Divide by 2 for as long as we can
        int next = n;
        int replacements = 0;
        while (next % 2 == 0) {
            next = next / 2;
            ++replacements;
        }

        if (next == 1) { 
            cache[n] = replacements;
            return replacements; 
        }
        // Hit an odd number, try both paths then cache the solution.
        replacements += 1 + std::min(min_replacements(next-1, cache), 
                                     min_replacements(next+1, cache));
        cache[n] = replacements;
        return replacements;
    }

    int integerReplacement(int n) {
        Cache cache;
        int i = 1;
        int replacements = 0;
        while (i != 0) {
            cache[i] = replacements;
            ++replacements;
            i = i << 1;
        }
        return min_replacements(n, cache);
    }
};

void test_integer_replacement() {
    Solution soln;
    assert(soln.integerReplacement(8) == 3);
    assert(soln.integerReplacement(9) == 4);
    assert(soln.integerReplacement(56) == 7);
}

int main(int argc, char** argv) {
    test_integer_replacement();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
