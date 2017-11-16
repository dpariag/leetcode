// Leetcode: https://leetcode.com/problems/longest-repeating-character-replacement/#/description
// Given a string of uppercase letters, you can replace any letter with another up to k times.
// Find the length of a longest substring containing one repeating letter that can be built.
// Example: "ABAB", k = 2 => return 4 ("AAAA")
// Example: "ABCCD", k = 2 => return 4 ("CCCCD")

// Brute Force: Consider all possible substrings, check if k+1 different letters occur in any,
// and return the longest one. O(n^3) time, O(n) time.
// Better: Scan the string with two pointers looking for a longest span requiring <= k replacements.
// O(n) time and space.

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

// Accepted. 13ms. Beats 53.92% of submissions, ties 31.57% of submissions.
class Solution {
public:
    int characterReplacement(const std::string& s, int k) {
        std::vector<int> char_counts(26, 0);
        int max_span = 0, left = 0, right = 0;
        int max_count = 0;

        while (right < s.size()) {
            auto r_index = s[right] - 'A';
            ++char_counts[r_index];
            max_count = std::max(max_count, char_counts[r_index]);
            auto replacements = (right - left + 1) - max_count;
            while (replacements > k) {
                auto l_index = s[left] - 'A';
                if (char_counts[l_index] == max_count) {
                    // Decrementing the max, must find new max
                    --char_counts[l_index];
                    max_count = *std::max_element(char_counts.begin(), char_counts.end());
                } else {
                    // Max doesn't change.
                    --char_counts[l_index];
                }
                ++left;
                replacements = (right - left + 1) - max_count;
            }
            max_span = std::max(max_span, (right - left + 1));
            ++right;
        }
        return max_span;
    }
};

void test_char_replacement() {
    Solution soln;
    assert(soln.characterReplacement("", 4) == 0);              // ""
    assert(soln.characterReplacement("A", 0) == 1);             // A
    assert(soln.characterReplacement("AAABB", 2) == 5);         // AAAAA
    assert(soln.characterReplacement("CCAAABB", 2) == 5);       // AAAAABB
    assert(soln.characterReplacement("CAAXABB", 2) == 5);       // AAAAABB
    assert(soln.characterReplacement("CAAXXABB", 2) == 5);      // CAAAAABB 
    assert(soln.characterReplacement("CAAXYZABB", 2) == 4);     // AAAAYZAB
    assert(soln.characterReplacement("ABCDEFG", 3) == 4);       // ABCGGGG 
}

int main(int argc, char** argv) {
    test_char_replacement();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
