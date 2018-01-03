// Leetcode: 
//Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 36ms. Beats 92.13% of submissions, ties 4.37% of submissions.
class Solution {
public:
    int firstUniqChar(const std::string& s) {
        int counts[256] = {0};

        // Count occurrences of each character
        for (auto ch : s) { counts[int(ch)]++; }

        // Scan the string looking for the first char with count == 1
        for (int i = 0; i < s.size(); ++i) {
            if (counts[int(s[i])] == 1) { return i; }
        }
        return -1;
    }
};

void test_first_unique_char() {
    Solution soln;

    assert(soln.firstUniqChar("") == -1);
    assert(soln.firstUniqChar("a") == 0);
    assert(soln.firstUniqChar("aa") == -1);
    assert(soln.firstUniqChar("aba") == 1);
    assert(soln.firstUniqChar("ababcdcde") == 8);
}


int main(int argc, char** argv) {
    test_first_unique_char();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
