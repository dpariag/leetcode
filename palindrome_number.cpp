// Leetcode: https://leetcode.com/problems/palindrome-number/description/
// Determine whether an integer is a palindrome. Do this without extra space.

// Brute Force: Extract digits of number into an array, then determine palidromicity. O(d) time/space
// Better: Build the mirror image of the number through modulo and multiplication. O(d) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 132ms. Beats 86.48% of submissions, ties 3.12% of submissions.
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) { return false; }
        int original = x, mirror = 0; 
        while (x != 0) {
            mirror = (mirror * 10) + (x % 10);
            x = x / 10;
        }
        return mirror == original;
    }
};

void test_is_palindrome() {
    Solution soln;
    assert(soln.isPalindrome(0) == true);
    assert(soln.isPalindrome(9) == true);
    assert(soln.isPalindrome(99) == true);
    assert(soln.isPalindrome(909) == true);
    assert(soln.isPalindrome(908) == false);
    assert(soln.isPalindrome(8008) == true);
    assert(soln.isPalindrome(412214) == true);
    assert(soln.isPalindrome(-412214) == false);
}

int main(int argc, char** argv) {
    test_is_palindrome();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
