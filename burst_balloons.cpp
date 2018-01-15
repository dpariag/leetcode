// Leetcode: https://leetcode.com/problems/burst-balloons/description/
// Given an array representing n balloons each labelled with a number, bursting balloon i will yield
// nums[i-1] * nums[i] * nums[i+i] coins. After the burst, nums[i] and nums[i+1] are adjacent.
// Find the maximum coins you can collect by bursting the balloons wisely.

// Brute Force: Iterate the array, burst i'th balloon and recurse on remaining balloons. O(n!) time.
// Better: Define table[i][j] = {max coins possible with balloons[i..j]. Iterate the diagonals,
// filling in ranges of len = {1,2,..,n}. Treat each coin in the range as if it were the last coin
// to be popped, which allows decomposing into independent subproblems.

#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 19ms. Beats 16.04% of submissions, ties 6.60% of submissions.
class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        if (nums.empty()) { return 0; }
        // table[i][j] = {max coins possible from nums[i..j]
        Table table(nums.size(), std::vector<int>(nums.size(), 0));

        for (int len = 1; len <= nums.size(); ++len) {
            for (int start = 0; start < nums.size(); ++start) {
                int end = std::min(start + len - 1, int(nums.size()-1));
                int max_coins = 0;
                for (int last_coin = start; last_coin <= end; ++last_coin) {
                    int left_coin = (start == 0) ? 1 : nums[start-1];
                    int right_coin = (end == int(nums.size())-1) ? 1 : nums[end+1];
                    int coins = left_coin * nums[last_coin] * right_coin; 
                    if (last_coin > start) coins += table[start][last_coin-1];
                    if (last_coin < end) coins += table[last_coin+1][end];
                    max_coins = std::max(max_coins, coins);
                }
                table[start][end] = max_coins;
            }
        }
        return table[0].back();
    }
};

bool test_max_coins(std::vector<int> nums, int expected) {
    Solution soln;
    return soln.maxCoins(nums) == expected;
}

void test_max_coins() {
    assert(test_max_coins({}, 0));
    assert(test_max_coins({13}, 13));
    assert(test_max_coins({3,1,5}, 35));
}

int main(int argc, char** argv) {
    test_max_coins();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
