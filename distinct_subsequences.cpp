// Leetcode: https://leetcode.com/problems/distinct-subsequences/description/
// Given strings S and T, count the number of distinct subsequences of S which equal T.
// A subsequence is formed from the original string by deleting zero or more characters 
// without disturbing the relative positions of remaining characters.

// Brute Force: Generate all subsequences of S, compare each to T. Exponential time.
// Better: Construct a table T[i][j] = # subsequences of T[0...i] found in S[0...j]
// Fill table using a recurrence relation (algorithm is analogous to Levenshtein dist). O(n^2) time

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 6ms. Beats 28.59% of submissions, ties 48.38% of submissions.
class Solution {
public:
    int numDistinct(std::string& s, std::string& t) {
        Table table(t.size(), std::vector<int>(s.size(), 0));

        // Initialize the first row
        table[0][0] = (s[0] == t[0]) ? 1 : 0;
        for (int col = 1; col < s.size(); ++col) {
            table[0][col] = table[0][col-1] + int(s[col] == t[0]);
        }

        for (int row = 1; row < table.size(); ++row) {
            for (int col = 1; col < table[0].size(); ++col) {
                if (s[col] == t[row]) {
                    table[row][col] = table[row-1][col-1] + table[row][col-1];
                } else {
                    table[row][col] = table[row][col-1];
                }
            }
        }
        return table.back().back();
    }
};

bool test_num_distinct(std::string s, std::string t, int expected) {
    Solution soln;
    return soln.numDistinct(s, t) == expected;
}

void test_num_distinct() {
    assert(test_num_distinct("artttx", "rtx", 3));
    assert(test_num_distinct("rxrttx", "rtx", 4));
    assert(test_num_distinct("rtxrttx", "rtx", 6));
    assert(test_num_distinct("banana", "ana", 4));
    assert(test_num_distinct("rabbbit", "rabbit", 3));
}

int main(int argc, char** argv) {
    test_num_distinct();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
