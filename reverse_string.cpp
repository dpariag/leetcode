// Leetcode: https://leetcode.com/problems/reverse-string/description/
// Write a function that takes a string as input and returns the string reversed.

// Approach: Swap the leftmost and rightmost characters, and move inwards. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 10ms. Beats 97.83% of submissions.
class Solution {
public:
    std::string reverseString(const std::string& s) {
        std::string reversed(s);

        int left = 0, right = s.size()-1;
        while (left < right) {
            std::swap(reversed[left++], reversed[right--]);
        }
        return reversed;
    }
};

void test_reverse() {
    Solution soln;

    assert(soln.reverseString("") == "");
    assert(soln.reverseString("A") == "A");
    assert(soln.reverseString("AB") == "BA");
    assert(soln.reverseString("ABC") == "CBA");
}

int main(int argc, char** argv) {
    test_reverse();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}