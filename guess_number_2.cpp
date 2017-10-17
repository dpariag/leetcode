// Leetcode: https://leetcode.com/problems/guess-number-higher-or-lower-ii/description/
// Play a guessing game over numbers 1..n. After each guess, the opponent tells you if the target
// number is higher or lower than your last guess. Each wrong guess of 'x' costs $x.
// How much money do you need to guarantee a win?

// The wording of the question is confusing. In general, we want to use binary search to narrow
// the range of guesses. However, the binary search path does not yield the minimum cost.
// For example: with {1,2,3,4}, the worst case for binary search costs 2 + 3 = 5. 
// However, choosing 3 then 1 (cost=$4) is a tighter upper bound (3 is a better first guess than 2).
// Brute Force: Try all initial guesses then recurse on left and right sub-ranges. 
// Better: Improve the above, by memo-izing based on [start,end] of the range.

#include <vector>
#include <iostream>
#include <assert.h>

using Cache = std::vector<std::vector<int>>; // Min cost for the range [i..j]

// Accepted. 23ms. Beats 34.31% of submissions. Ties 2.14% of submissions.
class Solution {
public:
    int get_money(int start, int end, Cache& cache) {
        if (start > end) { return 0; }

        // Check cache!
        if (cache[start][end] != -1) { return cache[start][end]; }

        int min_cost = std::numeric_limits<int>::max();
        // Try each initial guess, then recurse on left and right ranges
        for (int i = start; i <= end; ++i) {
            // First guess is wrong + worst case over (left, right) ranges
            auto cost = i + std::max(get_money(start, i-1, cache), get_money(i+1, end, cache));
            // Take the minimum over all first guess worst cases
            min_cost = std::min(min_cost, cost); 
        }
        // Update cache!
        cache[start][end] = min_cost;
        return min_cost;
    }

    int getMoneyAmount(int n) {
        Cache cache(n+1, std::vector<int>(n+1, -1));

        for (int i = 1; i <= n; ++i) {
            cache[i][i] = 0;                                // range of 1 costs 0
            if (i+1 < cache[i].size()) cache[i][i+1] = i;   // range of 2 costs the smaller one
            if (i+2 < cache[i].size()) cache[i][i+2] = i+1; // range of 3 costs the middle one
        }
        return get_money(1, n, cache);
    }
};

void test_guess_money() {
    Solution soln;
    assert(soln.getMoneyAmount(1) == 0);
    assert(soln.getMoneyAmount(2) == 1);
    assert(soln.getMoneyAmount(3) == 2);
    assert(soln.getMoneyAmount(4) == 4);
    assert(soln.getMoneyAmount(7) == 10);
}

int main(int argc, char** argv) {
    test_guess_money();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
