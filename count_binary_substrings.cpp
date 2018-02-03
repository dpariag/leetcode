// Leetcode: https://leetcode.com/problems/count-binary-substrings/description/
// Give a string s, count the number of non-empty substrings that have the same number of 0's and 1's, 
// and all the 0's and all the 1's in the substrings are consecutive.

// Approach: Count blocks of the same character. When switching blocks, start counting matches.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 57ms. Beats 33.72% of submissons, ties 22.37% of submissions.
class Solution {
public:
    int countBinarySubstrings(const std::string& s) {
        int i = 1, count = 0, cur_block = 1, prev_block = 0;

        while (i < s.size()) {
            if(s[i] == s[i-1]) {
                ++cur_block;
            } else {
                prev_block = cur_block;
                cur_block = 1;
            }

            if (cur_block <= prev_block) {
                ++count;
            }
            ++i;
        }
        return count;
    }
};

void test_count_binary_strings() {
    Solution soln;

    assert(soln.countBinarySubstrings("00110011") == 6);
    assert(soln.countBinarySubstrings("10101") == 4);
    assert(soln.countBinarySubstrings("10") == 1);
    assert(soln.countBinarySubstrings("00000") == 0);
    assert(soln.countBinarySubstrings("1111") == 0);
    assert(soln.countBinarySubstrings("1010") == 3);
}

int main(int argc, char** argv) {
    test_count_binary_strings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
