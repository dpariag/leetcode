// Leetcode: https://leetcode.com/problems/valid-palindrome/description/ 
// Determine if a string is a palindrome, considering only alphanumeric characters and ignoring case.

// Brute Force: Copy the string, removing non alphanumeric characters then determine 
// if it's a palindrome. O(n) time and space.
// Better: Scan using left and right pointers, but skip non-alphanumeric characters. 
// O(n) time and O(1) space.

#include <string>
#include <cctype>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 94.17% of submissions, ties 5.83% of submissions.
class Solution {
    public:
        bool isPalindrome(const std::string& s) {
            int left = 0, right = s.size() - 1;

            while (left <= right) {
                while (left <= right && !std::isalnum(s[left])) { ++left; }
                while (right >= left && !std::isalnum(s[right])) { --right; }

                if (left <= right) {
                    if (std::tolower(s[left]) != std::tolower(s[right])) { return false; }
                }
                ++left, --right;
            }
            return true;
        }
};

void test_is_palindrome() {
    Solution soln;

    assert(soln.isPalindrome("") == true);
    assert(soln.isPalindrome("a") == true);
    assert(soln.isPalindrome("aa") == true);
    assert(soln.isPalindrome("aab") == false);
    assert(soln.isPalindrome("bab") == true);
    assert(soln.isPalindrome("ba1") == false);
    assert(soln.isPalindrome("1a1") == true);
    assert(soln.isPalindrome("1;a1") == true);
    assert(soln.isPalindrome("1;a;1") == true);
    assert(soln.isPalindrome("1;a;**1") == true);
    assert(soln.isPalindrome("&&1;a;**1") == true);
    assert(soln.isPalindrome("1;a;**1$$$$") == true);
    assert(soln.isPalindrome("((((1;a;**1$$$$") == true);
    assert(soln.isPalindrome("abab****baba") == true);
    assert(soln.isPalindrome("abab***baba") == true);
    assert(soln.isPalindrome("abab**baba") == true);
    assert(soln.isPalindrome("abab*baba") == true);
    assert(soln.isPalindrome("ababbaba") == true);
}

int main(int argc, char** argv) {
    test_is_palindrome();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
