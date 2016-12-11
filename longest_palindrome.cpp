// Leetcode: https://leetcode.com/problems/longest-palindrome/
// Given a string of lowercase and/or uppercase letters, find the length of the longest palindrome
// that can be built with those letters. Example: "abccccdd" => return 7 (e.g., "dccaccd").
// Assume the length of the string will not exceed 1,010 characters

// Brute Force: Build all possible substrings of length n, n-1, .. 1, check which are palindromes.
// Better: Count instances of each letter, then the longest possible palindromes are comprised 
// of the longest odd sequence + all even sequences + all odd sequences with one letter ommitted.
// O(n) time and O(1) space.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

const unsigned num_letters = 'z' - 'A' + 1;

// Accepted. 3ms. Beats 61.39% of submissions, ties 38.61% of submissions.
class Solution {
public:
    int longestPalindrome(const std::string& s) {
        int letter_counts[num_letters] = {0};
        for (auto ch : s) {
            letter_counts[ch - 'A']++;
        }

        bool has_odd_counts = false;
        int length = 0;
        for (auto i = 0; i < num_letters; ++i) {
            if (letter_counts[i] % 2 == 0) {
                length += letter_counts[i];
            } else {
                length += letter_counts[i] - 1;
                has_odd_counts = true;
            }
        }
        return (has_odd_counts) ? length + 1 : length;
    }
};

void test_longest_palindrome() {
    Solution soln;
    assert(soln.longestPalindrome("abzzzzdd") == 7);
    assert(soln.longestPalindrome("") == 0);
    assert(soln.longestPalindrome("x") == 1);
    assert(soln.longestPalindrome("xxxxxx") == 6);
    assert(soln.longestPalindrome("xxxxxxxxx") == 9);
    assert(soln.longestPalindrome("xxxxxxxxxaagh") == 11);
    assert(soln.longestPalindrome("abccccdd") == 7);
    assert(soln.longestPalindrome("xxxyyyzzz") == 7);
    assert(soln.longestPalindrome("xxxxxyyyzzz") == 9);
}

int main(int argc, char** argv) {
    test_longest_palindrome();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
