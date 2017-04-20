// Leetcode: https://leetcode.com/problems/reverse-vowels-of-a-string/#/description
// Write a function that takes a string as input and reverse only the vowels of a string.
// Example: "hello" --> "holle", "leetcode" --> "leotcede".

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 68.94% of submissions, ties 31.06% of submissions.
class Solution {
public:
    inline bool is_vowel(const char ch) {
        return (ch == 'a' || ch == 'A' || ch == 'e' || ch == 'E' || ch == 'i' || ch == 'I' || 
                ch == 'o' || ch == 'O' || ch == 'u' || ch == 'U');
    }

    std::string reverseVowels(const std::string&  s) {
        if (s.empty()) { return s; }
        std::string reversed = s;
        int left = 0, right = reversed.size() - 1;
        while (left < right) {
            while (left < reversed.size() && !is_vowel(reversed[left])) ++left;
            while (right > 0 && !is_vowel(reversed[right])) --right;
            if (left <= right) {
                std::swap(reversed[left], reversed[right]);
                ++left; --right;
            }
        }
        return reversed;
    }
};

void test_reverse_vowels() {
    Solution soln;
    assert(soln.reverseVowels("") == "");
    assert(soln.reverseVowels("e") == "e");
    assert(soln.reverseVowels("aA") == "Aa");
    assert(soln.reverseVowels("ex") == "ex");
    assert(soln.reverseVowels("exe") == "exe");
    assert(soln.reverseVowels("axe") == "exa");
    assert(soln.reverseVowels("axE") == "Exa");
    assert(soln.reverseVowels("hello") == "holle");
    assert(soln.reverseVowels("leetcode") == "leotcede");
    assert(soln.reverseVowels("aaaaa") == "aaaaa");
    assert(soln.reverseVowels("zZz") == "zZz");
    assert(soln.reverseVowels("aeiou") == "uoiea");
}

int main(int argc, char** argv) {
    test_reverse_vowels();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
