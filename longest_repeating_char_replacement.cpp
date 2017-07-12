// Leetcode: https://leetcode.com/problems/longest-repeating-character-replacement/#/description
// Given a string of uppercase English letters, you can replace any letter with another up to k times.
// Find the length of a longest substring containing one repeating letter that can be built.
// Example: "ABAB", k = 2. Build "AAAA" => return 4.

// Brute Force: Consider all possible substrings, check if each contains only 2 letters with one
// of the letters occuring <= k times. O(n^3) time.
// Better: Scan the string with two pointers looking for the longest span containing 2 letters
// with one of them occurring <= k times. O(n) time.

#include <string>
#include <iostream>
#include <assert.h>

class Solution {
public:
    int characterReplacement(const std::string& s, int k) {
        char first_char = 'a', second_char = 'a';
        int left = 0, right = 0;
        int max_span = 0;

        while (right < s.size()) {
            if (first_char == 'a') {
              first_char = s[right];
            } else if (s[right] != first_char && second_char == 'a') {
               second_char = s[right];
            } else {
                if (s[right] != first_char && s[right] != second_char) {
                    left = right;
                }
            }
            max_span = std::max(max_span, right - left + 1);
            ++right;
        }
        std::cout << "Max span = " << max_span << std::endl;
        return max_span;
    }
};

void test_char_replacement() {
    Solution soln;
    assert(soln.characterReplacement("AAAAA", 5) == 5);
    assert(soln.characterReplacement("AAABB", 2) == 5);
    assert(soln.characterReplacement("AABBB", 2) == 5);
    assert(soln.characterReplacement("AABCBB", 1) == 3);
    assert(soln.characterReplacement("AABCBB", 2) == 3);
    assert(soln.characterReplacement("ABCDEFG", 22) == 2);
}

int main(int argc, char** argv) {
    test_char_replacement();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
