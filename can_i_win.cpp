// Leetcode: https://leetcode.com/problems/can-i-win/description/
// Suppose two players take turns drawing from a common pool of numbers of 1..N without replacement,
// until the sum of chosen numbers reaches a total >= X. Determine if the first player can force
// a win if both players play optimally. N <= 20 and X <= 300

// Brute Force: Use recursion to simulate each player's moves. Track the total sum. Exponential time.
// Better: Use memoization (total, numbers already chosen) --> boolean (winnable?).

#include <vector>
#include <iostream>
#include <unordered_set>
#include <assert.h>

std::string P(bool p1_turn) {
    return p1_turn ? "P1 " : "P2 ";
}

struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const {
        return p.first * 13 + p.second * 17;
    }
};

using Cache = std::unordered_set<std::pair<int,int>, PairHash>; // (current_total, chosen)

class Solution {
public:
    bool can_i_win(int n, int total, int desired_total, int chosen, bool p1_turn, 
                   Cache& cache) {
        //std::cout << std::endl;
        //std::cout << "*Chosen = " << chosen << " Desired = " << desired_total << std::endl;
        if (total >= desired_total) { return true; }
        if (cache.count(std::make_pair(total, chosen))) { return true; }
        int wins = 0, value = 1;
        for (int choice = 1; choice < (1 << n); choice <<= 1) {
            if ((choice & chosen) == 0) {
                chosen |= choice;
                total += value;
                //std::cout << P(p1_turn) << "chooses " << value << " total = " << total << std::endl;
                if (total >= desired_total) {
                    //std::cout << P(p1_turn) << "wins" << std::endl;
                    cache.emplace(std::make_pair(total-value, chosen^choice));
                    ++wins;
                    return true;
                } else {
                    //std::cout << "Chosen = " << chosen << std::endl;
                    auto opp_won = can_i_win(n, total, desired_total, chosen, !p1_turn, cache);
                    if (!opp_won) {
                        cache.emplace(std::make_pair(total-value, chosen^choice));
                        return true; 
                    } // found a winning play
                }
                total -= value;
                chosen = chosen ^ choice; // clear the last choice
            }
            ++value;
        }
        return false;
    }

    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        Cache cache;
        if ((maxChoosableInteger * (maxChoosableInteger+1) / 2) < desiredTotal) { return false; }
        return can_i_win(maxChoosableInteger, 0, desiredTotal, 0, true, cache);
    }
};

void test_can_i_win() {
    Solution soln;
    assert(soln.canIWin(5,50) == false);
    assert(soln.canIWin(10,40) == false);
    assert(soln.canIWin(4,6) == true);
    assert(soln.canIWin(10, 0) == true);
    assert(soln.canIWin(10, 1) == true);
    assert(soln.canIWin(10, 11) == false);
}


int main(int argc, char** argv) {
    test_can_i_win();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
