// Leetcode: https://leetcode.com/problems/can-i-win/description/
// Suppose two players take turns drawing from a common pool of numbers of 1..N without replacement,
// until the sum of chosen numbers reaches a total >= X. Determine if the first player can force
// a win if both players play optimally. N <= 20 and X <= 300

// Brute Force: Use recursion to simulate each player's moves. Track the total sum. Exponential time.
// Better: Use memoization (total, numbers already chosen) to remember winning plays

#include <vector>
#include <iostream>
#include <unordered_set>
#include <assert.h>

struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const {
        return p.first * 13 + p.second * 17;
    }
};

using Cache = std::unordered_set<std::pair<int,int>, PairHash>; // (total, chosen) -> bool

// Accepted. 123ms. Beats 59.96% of submissions, ties 0.67%
class Solution {
public:
    bool can_i_win(int n, int total, int desired_total, int chosen, Cache& cache) {
        if (total >= desired_total) { return true; }
        if (cache.count(std::make_pair(total, chosen))) { return true; }

        // Try every choice still available 
        int value = 1, choice = 1;
        for ( ; choice < (1 << n); choice <<= 1) {
            if ((choice & chosen) == 0) {
                chosen |= choice;
                total += value;
                if (total >= desired_total) {
                    // A win!
                    cache.emplace(std::make_pair(total-value, chosen^choice));
                    return true;
                } else {
                    // Let the opponent play
                    auto opp_won = can_i_win(n, total, desired_total, chosen, cache);
                    if (!opp_won) {
                        // Opponent couldn't win, so this is a winning play for me
                        cache.emplace(std::make_pair(total-value, chosen^choice));
                        return true; 
                    }
                }
                total -= value;
                chosen = chosen ^ choice; // clear the last choice
            }
            ++value;
        }
        // Tried all available plays, and couldn't win.
        return false;
    }

    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        Cache cache;
        // A quick test to make sure a win is possible
        if ((maxChoosableInteger * (maxChoosableInteger+1) / 2) < desiredTotal) { return false; }
        return can_i_win(maxChoosableInteger, 0, desiredTotal, 0, cache);
    }
};

void test_can_i_win() {
    Solution soln;
    assert(soln.canIWin(10, 0) == true);
    assert(soln.canIWin(10, 1) == true);
    assert(soln.canIWin(10, 11) == false);
    assert(soln.canIWin(4,6) == true);
    assert(soln.canIWin(5,50) == false);
    assert(soln.canIWin(10,40) == false);
}


int main(int argc, char** argv) {
    test_can_i_win();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
