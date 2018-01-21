// Leetcode: https://leetcode.com/problems/valid-word-abbreviation/description/
// Given a non-empty string s and an abbreviation abbr, return whether s matches abbr.

// Brute Force: Generate all valid abbreviations of word, then see if abbr is one of them. O(2^n) time.
// Better: Scan word and abbr, matching characters, and skipping ranges of word when abbr contains numbers.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 12.15% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool validWordAbbreviation(const std::string& word, const std::string& abbr) {
        int i = 0, j = 0;

        while (i < word.size() && j < abbr.size()) {
            if (std::isalpha(abbr[j])) {
                if (abbr[j++] != word[i++]) { return false; }
            } else {
                // abbr[j] is a digit
                int count = 0;
                if (abbr[j] == '0') { return false; } // no leading zeros!
                while (std::isdigit(abbr[j])) {
                    count = (count * 10) + (abbr[j++] - '0');
                }
                i += count;
            }
        }
        return i == word.size() && j == abbr.size();
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
