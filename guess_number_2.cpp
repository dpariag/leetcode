// Leetcode: https://leetcode.com/problems/guess-number-higher-or-lower-ii/description/
// Play a guessing game over numbers 1..n. After each guess, the opponent tells you if the target
// number is higher or lower than your last guess. Each wrong guess of 'x' costs $x.
// How much money do you need to guarantee a win?

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>
#include <unordered_map>

// Start 8:24pm
// Done on paper: 8:32pm
// Done coding: 8:34pm
// Question is confusing, didn't understand looking for "best strategy".
// Pure Binary search is not the optimal cost strategy!
// Start coding again at 9:05pm
// Accepted by Leetcode  9:39pm

struct Hash {
    size_t operator()(const std::pair<int,int>& p) const {
        return p.first * 7 + p.second * 13;
    }
};

using Cache = std::unordered_map<std::pair<int,int>, int, Hash>;

// Accepted. 206ms. Beats 4.09% of submissions. Ties < 1% of submissions.
class Solution {
public:
    // start and end are values (guesses) not array indices
    int get_money(int start, int end, Cache& cache) {
        if (start > end) { return 0; }
        if (start == end) { return 0; } // range of size 1
        if ((end - start) == 1) { return start; }   // range of size 2
        if ((end - start) == 2) { return start + 1; } // range of size 3

        auto found = cache.find(std::make_pair(start,end));
        if (found != cache.end()) {
            return found->second;
        }

        int min_cost = std::numeric_limits<int>::max();
        // 4 or more... and not in the cache
        for (int i = start; i <= end; ++i) {
            auto cost = i + std::max(get_money(start, i-1, cache), get_money(i+1, end, cache));
            min_cost = std::min(min_cost, cost); 
        }
        cache.emplace(std::make_pair(start,end), min_cost);
        return min_cost;
    }

    int getMoneyAmount(int n) {
        Cache cache;
        return get_money(1, n, cache);
    }
};

void test_guess_money() {
    Solution soln;
    assert(soln.getMoneyAmount(7) == 10);
    assert(soln.getMoneyAmount(1) == 0);
    assert(soln.getMoneyAmount(2) == 1);
    assert(soln.getMoneyAmount(3) == 2);
    assert(soln.getMoneyAmount(4) == 4);
}

int main(int argc, char** argv) {
    test_guess_money();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
