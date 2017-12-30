// Leetcode: https://leetcode.com/problems/palindrome-permutation/description/
// Given a string, determine if a permutation of the string could form a palindrome.

// Brute Force: Generate all permutations of the string, check if each is a palindrome.
// Better: Count characters in the string. A palindrome is possible if only one character has an odd count.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 16.22% of submssions, ties 83.78% of submissions.
const int cNUM_CHARS = 255;
class Solution {
public:
    bool canPermutePalindrome(const std::string& s) {
        int counts[cNUM_CHARS];

        for (int i = 0; i < cNUM_CHARS; ++i) { counts[i] = 0; }
        for (auto ch : s) { counts[int(ch)]++; }
        
        int num_odd = 0, num_even = 0;
        for (int i = 0; i < cNUM_CHARS; ++i) { 
            if (counts[i] % 2) {
                ++num_odd;
            } else {
                ++num_even;
            }
        }
        return num_odd <= 1;
    }
};

void test_palindrome_permutation() {
    Solution soln;

    assert(soln.canPermutePalindrome("a") == true);
    assert(soln.canPermutePalindrome("aa") == true);
    assert(soln.canPermutePalindrome("aaa") == true);
    assert(soln.canPermutePalindrome("baaa") == false);
    assert(soln.canPermutePalindrome("baaab") == true);
}

int main(int argc, char** argv) {
    test_palindrome_permutation();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
