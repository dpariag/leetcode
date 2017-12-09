// Leetcode: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/ 
// Given the price of a stock on day i and a non-negative transaction fee, calculate the maximum profit possible.
// You may complete as many transactions as you like, but each buy/sell pair incurs a transaction fee. 
// You must sell the stock share before you buy again.

// Approach: Use two arrays. 
// buy[i] tracks the max profit achievable ending on day i with a buy as the last transaction.
// sell[i] tracks the max profit achievable ending on day i with a sell as the last transaction.
// O(n) time and space. Save space by tracking just the last buy and last sell. O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 142ms. Beats 68.48% of submissions, ties 9.80% of submissions.
class Solution {
public:
    int maxProfit(const std::vector<int>& prices, int fee) {
        int prev_buy = -prices[0], next_buy = 0;
        int prev_sell = 0, next_sell = 0;

        for (int i = 1; i < prices.size(); ++i) {
            next_buy = std::max(prev_buy, prev_sell - prices[i]);
            next_sell = std::max(prev_sell, prev_buy + prices[i] - fee);
            prev_buy = next_buy;
            prev_sell = next_sell;
        }
        return next_sell;
    }
};

void test_max_profit() {
    Solution soln;
    assert(soln.maxProfit({1,3,2,8,4,9}, 2) == 8);
}

int main(int argc, char** argv) {
    test_max_profit();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}