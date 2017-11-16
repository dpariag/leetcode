// Leetcode: https://leetcode.com/problems/reverse-words-in-a-string/
// Given an input string, reverse the string word by word.
// Example: Given s = "the sky is blue", return "blue is sky the".

// Brute Force: Allocate a temporary string, copy in words right to left. O(n) time and space.
// Better: Can be done in place by first reversing the individual words in the string,
// then reversing the entire string. 
// Example: "the sky is blue" --> "eht yks si eulb" --> "blue is sky the"

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

// Accepted. 9ms. Beats 25.48% of submissions, ties 52.97% of submissions.
class Solution {
public:
    // Remove leading, trailing, and duplicate inter-word spaces.
    inline void trim_string(std::string& s) {
        // trim trailing space
        while (s.back() == ' ') s.pop_back();

        // skip leading spaces
        size_t to = 0, from = 0;
        while (from < s.size() && s[from] == ' ') ++from;

        // shift words left, removing duplicate spaces       
        while (from < s.size()) {
            while (from < s.size() && s[from] != ' ') {
                s[to] = s[from];
                ++to; ++from;
            }
            if (from < s.size() && to < s.size()) s[to++] = ' ';
            while (from < s.size() && s[from] == ' ') ++from;
        }
        // Remove trailing junk
        s.erase(to);
    }

    void reverseWords(std::string &s) {
        trim_string(s);
        
        // Reverse individual words in the string, in-place
        size_t start = 0;
        while (start < s.size()) {
            while (start < s.size() && s[start] == ' ') ++start;
            size_t end = start;
            while (end < s.size() && s[end] != ' ') ++end;

            size_t i = start, j = end - 1;
            while (i < j) {
                std::swap(s[i], s[j]);
                ++i; --j;
            }
            start = end;
        }
        // Reverse the whole string
        std::reverse(s.begin(), s.end());
    }
};

bool test_reverse_words(std::string to_reverse, const std::string& reversed) {
    Solution soln;
    soln.reverseWords(to_reverse);
    return to_reverse == reversed; 
}

void test_reverse_words() {
    assert(test_reverse_words("", ""));
    assert(test_reverse_words(" ", ""));
    assert(test_reverse_words("     ", ""));
    assert(test_reverse_words("reverse", "reverse"));
    assert(test_reverse_words(" reverse", "reverse"));
    assert(test_reverse_words(" reverse ", "reverse"));
    assert(test_reverse_words("the sky is blue", "blue is sky the"));
    assert(test_reverse_words("the the the", "the the the"));
    assert(test_reverse_words("otto otto", "otto otto"));
    assert(test_reverse_words("otto     otto", "otto otto"));
    assert(test_reverse_words("  otto     otto  ", "otto otto"));
}

int main(int argc, char** argv) {
    test_reverse_words();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
