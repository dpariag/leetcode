// Leetcode: https://leetcode.com/problems/optimal-account-balancing/description/
// Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.
// Transactions are represented as integer triples [X,Y,Z] meaning PersonX gave Z dollars to PersonY.

// Approach: Build a graph where vertices are people, outgoing edges represent money given,
// and incoming edges represent money received. Calclate net debt for each person, and ignore people with zero debt.
// Note that the array of debts is zero-sum, (n-1) transfers will always settle the debt!
// Exhaustively search the graph for a path of length < (n-1)
// For the i'th person, try a transfer to every other person with non-zero, opposite sign debt, then
// recurse on the i+1st person. If no person with non-zero, opposite sign debt exists then return path length = 0.

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Transactions = std::vector<std::vector<int>>;
using OwedMap = std::unordered_map<int, int>; // PersonID -> Amount Owed

// Accepted. 31ms. Beats 37.83% of submissions.
class Solution {
public:
    int minTransfers(const Transactions& transactions) {
        OwedMap owed;

        for (auto& t : transactions) {
            int from = t[0], to = t[1], amount = t[2];
            owed[from] += amount;
            owed[to] -= amount;
        }

        std::vector<int> amounts;
        for (auto o : owed) {
            if (o.second != 0) { amounts.emplace_back(o.second); }
        }

        return shortest_path(amounts, 0);
    }

    int shortest_path(std::vector<int>& amounts, int start) {
        int path_len = std::numeric_limits<int>::max();
        // Skip past leading zeroes
        while (start < amounts.size() && amounts[start] == 0) { ++start; }
        
        // Try a transfer to every person whose debt is non-zero and the opposite sign, then
        // recurse on start+1. Note that people can be "visited" more than once!
        for (int i = start+1; i < amounts.size(); ++i) {
            if ((amounts[start] < 0 && amounts[i] > 0) || (amounts[start] > 0 && amounts[i] < 0)) {
                amounts[i] += amounts[start];
                path_len = std::min(path_len, 1 + shortest_path(amounts, start+1));
                amounts[i] -= amounts[start];
            }
        }
        return path_len == std::numeric_limits<int>::max() ? 0 : path_len;
    }
};

bool test_account_balancing(Transactions t, int expected) {
    Solution soln;

    auto min_transactions = soln.minTransfers(t);
    return min_transactions == expected;
}

void test_account_balancing() {
    assert(test_account_balancing({{1,5,8},{8,9,8},{2,3,9},{4,3,1}}, 4));
    assert(test_account_balancing({{0,1,10}}, 1));
    assert(test_account_balancing({{0,1,10}, {1,0,10}}, 0));
    assert(test_account_balancing({{0,1,9}, {1,2,5}, {2,0,5}}, 1));
    assert(test_account_balancing({{0,1,10}, {1,2,5}, {2,3,5}, {3,4,20}, {4,0,5}}, 2));
}

int main(int argc, char** argv) {
    test_account_balancing();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
