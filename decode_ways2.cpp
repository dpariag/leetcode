// Leetcode: https://leetcode.com/problems/decode-ways-ii/description/ 
//

// Brute Force: Recursion + backtracking to fill in all '*'s, then calculate 
// number of ways to decode each filled in string. (exponential time).
// Better: Use DP. For the i'th character:
// 1) It adds decodings based on s[0..i-1]
// 2) If s[i-1] is a '1' then it also adds decodings based on s[0..i-2] 
// 3) If s[i-2] is a '2' then it also adds decodings based on s[0..i-2]
// Treat '*' carefully. Adds 9 new decodings to s[0..i-1], 
// but when s[i-1] is a '*' it can be treated as either a '1' or a '2'.

#include <vector>
#include <stdint.h>
#include <iostream>
#include <assert.h>

static const int MAX = 1000000007;

// Accepted. 66ms. Beats 62.80% of submissions, ties 4.42% of submissions.
class Solution {
public:
    int numDecodings(const std::string& s) {
        if (s.empty() || s.front() == '0') { return 0; }

        std::vector<int64_t> ways(s.size(), 0);
        ways[0] = (s[0] == '*') ? 9 : 1;

        for (int i = 1; i < s.size(); ++i) {
            auto two_back = (i == 1) ? 1 : ways[i-2];
            if (s[i] == '*') {
               ways[i] = (ways[i-1] * 9) % MAX; 
               if (s[i-1] == '1') {
                   ways[i] = (ways[i] + two_back * 9) % MAX;
               } else if (s[i-1] == '2') {
                   ways[i] = (ways[i] + two_back * 6) % MAX;
               } else if (s[i-1] == '*') {
                   ways[i] = (ways[i] + two_back * 15) % MAX;
               }
            } else {
                // s[i] is a digit
                if (s[i] != '0') { ways[i] = ways[i-1]; } // '0' is not a letter on it's own
                if (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6')) {
                    ways[i] = (ways[i] + two_back) % MAX;
                } else if (s[i-1] == '*') {
                    ways[i] = (ways[i] + two_back) % MAX;
                    if (s[i] <= '6') { ways[i] = (ways[i] + two_back) % MAX; }
                }
            }
        }
        return ways.back();
    }
};

void test_num_decodings() {
    Solution soln;

    assert(soln.numDecodings("**********1111111111") == 133236775);
    assert(soln.numDecodings("0") == 0);
    assert(soln.numDecodings("*1*1*0") == 404);
    assert(soln.numDecodings("") == 0);
    assert(soln.numDecodings("*") == 9);
    assert(soln.numDecodings("1*") == 18);
    assert(soln.numDecodings("1*2") == 20);
    assert(soln.numDecodings("1*2*") == 288);
}

int main(int argc, char** argv) {
    test_num_decodings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
