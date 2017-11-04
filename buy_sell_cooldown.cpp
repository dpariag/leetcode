// Leetcode: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
// Given an array of stock prices, find the max profit obtainable with the foll. restrictions:
// - you must sell the stock before buying it again.
// - you must allow at least one day of cooldown between transactions.

// Approach: Derive the max profit on day i+1 from the max profit on day i.
// Store the max profit obtainable if day i ends with either a buy or a sell. 
// Then apply the foll. rules:
//      buy[i] = max(buy[i-1], sell[i-2] - prices[i])
//      sell[i] = max(sell[i-1], buy[i-1] + prices[i])

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>


class Solution {
public:
    int maxProfit(const std::vector<int>& prices) {
        if (prices.size() < 2) { return 0; }
        std::vector<int> buy(prices.size(), 0);  // max profit on day i, if ending with a buy
        std::vector<int> sell(prices.size(), 0); // max profit on day i, if ending with a sell

        buy[0] = -prices[0];
        buy[1] = std::max(-prices[0], -prices[1]);  // buy on either day 0 or day 1
        sell[1] = std::max(prices[1] - prices[0], 0); // buy on 0 and sell on 1, or do nothing 

        for (int i = 2; i < prices.size(); ++i) {
            buy[i] = std::max(buy[i-1], sell[i-2]-prices[i]);
            sell[i] = std::max(sell[i-1], buy[i-1]+prices[i]);
        }
        return std::max(0, sell.back()); // doing nothing always yields 0
    }
};

void test_max_profit() {
    Solution soln;
    
    assert(soln.maxProfit({2,1}) == 0);
    assert(soln.maxProfit({7,4,1,2}) == 1);
    assert(soln.maxProfit({3,2,6,5,0,3}) == 7);
    assert(soln.maxProfit({4,1,2}) == 1);
    assert(soln.maxProfit({1,2,8,10,0,6,5,20}) == 27);
    assert(soln.maxProfit({1,2,3,4,10,0,4,1,4}) == 12);
    assert(soln.maxProfit({1,2,3,4,3,2,1,5}) == 7);
    assert(soln.maxProfit({1,2,3,4,5,1,5}) == 7);
    assert(soln.maxProfit({1,2,3,4,4,4,4,3,2,1,5}) == 7);
    assert(soln.maxProfit({1,2,8,10,0,6,5,20,15,10,30}) == 47);
    assert(soln.maxProfit({9,9,0,3,0,7,7,7,4,1,5,0,1,7}) == 17);
}

int main(int argc, char** argv) {
    test_max_profit();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
