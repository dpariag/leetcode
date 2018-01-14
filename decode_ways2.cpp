// Leetcode: https://leetcode.com/problems/decode-ways-ii/description/ 
//

// Brute Force:
// Better:

#include <vector>
#include <stdint.h>
#include <iostream>
#include <assert.h>

static const int MAX = 1000000007;

// Accepted. 72ms. Beats 51.01% of submissions, ties 4.42% of submissions.
class Solution {
public:
    int numDecodings(const std::string& s) {
        if (s.empty()) { return 0; }

        std::vector<int64_t> ways(s.size(), 0);
        if (s[0] != '0') {
          ways[0] = (s[0] == '*') ? 9 : 1;          
        }

        for (int i = 1; i < s.size(); ++i) {
            auto two_back = (i == 1) ? 1 : ways[i-2];
            if (s[i] == '*') {
               ways[i] = (ways[i-1] * 9) % MAX;
               if (s[i-1] == '1') {
                   ways[i] = (ways[i] + ((two_back * 9) % MAX)) % MAX;
               } else if (s[i-1] == '2') {
                   ways[i] = (ways[i] + ((two_back * 6) % MAX)) % MAX;
               } else if (s[i-1] == '*') {
                   ways[i] = (ways[i] + ((two_back * 15) % MAX)) % MAX;
               }
            } else {
                // s[i] is a digit
                if (s[i] != '0') { ways[i] = ways[i-1]; }
                if (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6')) {
                    ways[i] = (ways[i] + two_back) % MAX;
                } else if (s[i-1] == '*') {
                    ways[i] = (ways[i] + two_back) % MAX;
                    if (s[i] <= '6') { ways[i] = (ways[i] + two_back) % MAX; }
                }
            }

        }
        std::cout << ways.back() << std::endl;
        return ways.back();
    }
};

void test_num_decodings() {
    Solution soln;
                                                     //881150112
                                                     //1000000007
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
