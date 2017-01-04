// Leetcode: https://leetcode.com/problems/reverse-words-in-a-string/
// Given an input string, reverse the string word by word.
// Example: Given s = "the sky is blue", return "blue is sky the".

// Brute Force:
// Better:
// "eulb si yks eht" --> "blue is sky the"
// "eht yks si eulb" --> "blue is sky the"

#include <vector>
#include <iostream>
#include <assert.h>

class Solution {
public:
    void reverseWords(std::string &s) {
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
    assert(test_reverse_words(" ", " "));
    assert(test_reverse_words("     ", "     "));
    assert(test_reverse_words("reverse", "reverse"));
    assert(test_reverse_words(" reverse", "reverse "));
    assert(test_reverse_words(" reverse ", " reverse "));
    assert(test_reverse_words("the sky is blue", "blue is sky the"));
    assert(test_reverse_words("the the the", "the the the"));
    assert(test_reverse_words("otto otto", "otto otto"));
    assert(test_reverse_words("otto     otto", "otto     otto"));
}

int main(int argc, char** argv) {
    test_reverse_words();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
