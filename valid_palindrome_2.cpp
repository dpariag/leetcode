// Leetcode: 
// Given a non-empty string s, determine if you can make it a palindrome by deleting at most 1 char.

// Brute Force: Test for palindromcity. If not, delete each char in turn and retest. O(n^2) time.
// Better: Scan the string from both ends, comparing characters. Allow one mismatch, using recursion
// to try both possibilities for the remainder of the string (after the mismatch). O(n) time.

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 126ms. Beats 48.61% of submissions, ties 4.86% of submissions.
class Solution {
public:

    bool valid_palindrome(const std::string& s, int left, int right, bool deleted) {
        while (left <= right) {
            if (s[left] == s[right]) {
                ++left; --right;
            } else {
                if (deleted) { return false; }
                if (s[left] == s[right-1] && valid_palindrome(s, left, right-1, true)) {
                    return true;
                } 
                if (s[left+1] == s[right] && valid_palindrome(s, left+1, right, true)) {
                    return true;
                } 
                return false;
            } 
        }
        return true;
    }

    bool validPalindrome(std::string s) {
        return valid_palindrome(s, 0, s.size() - 1, false);
    }
};

void test_valid_palindrome() {
    Solution soln;
    assert(soln.validPalindrome("a") == true);
    assert(soln.validPalindrome("ab") == true);
    assert(soln.validPalindrome("aba") == true);
    assert(soln.validPalindrome("abac") == true);
    assert(soln.validPalindrome("abca") == true);
    assert(soln.validPalindrome("cabac") == true);
    assert(soln.validPalindrome("cdbac") == false);
    assert(soln.validPalindrome("cdbdac") == true);
    assert(soln.validPalindrome("ebcbbececabbacecbbcbe") == true);
}

int main(int argc, char** argv) {
    test_valid_palindrome();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
