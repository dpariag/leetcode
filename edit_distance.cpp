// Leetcode: https://leetcode.com/problems/edit-distance/description/
// Given two words, find the minimum number of edits (insert/delete/substitute) required to 
// convert word1 to word2.

// Brute Force: Recursively edit each position in word1, stopping at word2. Exponential time.
// Better: Compute the Levenshtein distance between the words (dynamic programming). O(n^2) time.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 9ms. Beats 44.69% of submissions, ties 52.24% of submissions.
class Solution {
public:
    inline int minDistance(const std::string& word1, const std::string& word2) {
        // Use a table with an extra row an column
        Table t(word1.size()+1, std::vector<int>(word2.size()+1, 0));

        // Fill in first row and column (edit distances are relative to the empty string)
        for (int row = 0; row <= word1.size(); ++row) { t[row][0] = row; }
        for (int col = 0; col <= word2.size(); ++col) { t[0][col] = col; }

        for (int row = 1; row <= word1.size(); ++row) {
            for (int col = 1; col <= word2.size(); ++col) {
                if (word1[row-1] == word2[col-1]) {
                    // last char is the same, same distance as t[row-1][col-1]
                    t[row][col] = t[row-1][col-1];
                } else {
                    // last char mismatch. 1 + shortest dist of (swap, delete, insert) respectively.
                    t[row][col] = 1 + std::min({t[row-1][col-1], t[row-1][col], t[row][col-1]});
                }
            }
        }
        return t.back().back();
    }
};

bool test_min_distance(std::string word1, std::string word2, int expected) {
    Solution soln;
    return soln.minDistance(word1, word2) == expected;
}

void test_min_distance() {
    assert(test_min_distance("sea", "ate", 3));
    assert(test_min_distance("abcd", "abc", 1));
    assert(test_min_distance("abcd", "edit", 4));
    assert(test_min_distance("abcd", "adit", 3));
    assert(test_min_distance("abcde", "adit", 4));
    assert(test_min_distance("pneumonoultramicroscopicsilicovolcanoconiosis", 
                             "ultramicroscopically", 27));
}

int main(int argc, char** argv) {
    test_min_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
