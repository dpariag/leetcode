// Leetcode: https://leetcode.com/problems/coin-change/description/

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Coins = std::vector<int>;
using Cache = std::unordered_map<int, int>; // Amount -> Min coins required

// Accepted. 252ms. Beats 9.41% of submissions, ties < 1% of submissions.
class Solution {
public:
    int coin_change(Coins& coins, int amount, Cache& cache) {
        if (amount == 0) { 
            return 0;
        }
        auto found = cache.find(amount);
        if (found != cache.end()) { return found->second; }

        int min_coins = std::numeric_limits<int>::max();
        for (int i = 0; i < coins.size(); ++i) {
            if (coins[i] <= amount) {
                int num_coins = coin_change(coins, amount - coins[i], cache);
                if (num_coins != -1) {
                    ++num_coins;
                    min_coins = std::min(min_coins, num_coins);
                }
            }
        }
        if (min_coins != std::numeric_limits<int>::max()) {
            cache[amount] = min_coins;
            return min_coins;
        }
        cache[amount] = -1;
        return -1;
    }

    int coinChange(Coins& coins, int amount) {
        // Sort in descending order
        Cache cache;
        std::sort(coins.begin(), coins.end(), [](int c1, int c2) {return c1 > c2;});
        auto num_coins = coin_change(coins, amount, cache);
        return num_coins;
    }
};

bool test_coin_change(Coins coins, int amount, int expected) {
    Solution soln;
    return soln.coinChange(coins, amount) == expected;
}

void test_coin_change() {
    assert(test_coin_change({2}, 3, -1));
    assert(test_coin_change({1,2,5}, 100, 20));
    assert(test_coin_change({1,2,5}, 101, 21));
    assert(test_coin_change({1,2,5}, 11, 3));
    assert(test_coin_change({186,419,83,408}, 6249, 20));
}

int main(int argc, char** argv) {
    test_coin_change();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}