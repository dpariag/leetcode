// Leetcode: https://leetcode.com/problems/decode-ways/#/description 
// A message containing letters from A-Z is encoded numerically using the mapping:
// 'A' -> 1, 'B' -> 2, ..., 'Z' -> 26
// Given an encoded message containing digits, determine the total number of ways to decode it.
// "12" -->"AB" (1 2) or "L" (12), so 2 ways

// Brute Force: Recursive enumeration. O(2^n) time.
// Better: DP. Build an array A[i] holds the number of ways to decode s[0..i-1]. 
// Note: A[i] can be obtained from A[i-1] and A[i-2] by examining s[i-2..i-1]. O(n) time and space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 16.10% of solutions, ties 83.32% of submissions.
class Solution {
public:
    int numDecodings(const std::string& s) {
        if (s.empty() || s[0] == '0') { return 0; }
        
        std::vector<int> ways(s.length()+1, 0); // extra slot
        ways[0] = 1;
        ways[1] = 1;
        for (int i = 2; i < ways.size(); ++i) {
            int one_char_mapping(s[i-1] - '0');
            if (one_char_mapping > 0) {
                ways[i] += ways[i-1]; // one valid character
            }

            int two_char_mapping((s[i-2] - '0')*10 + one_char_mapping);
            if (s[i-2] > '0' && two_char_mapping >= 1 && two_char_mapping <= 26) {
                ways[i] += ways[i-2]; // two valid characters
            }
        }
        return ways.back();
    }
};

void test_num_decodings() {
    Solution soln;

    assert(soln.numDecodings("") == 0);
    assert(soln.numDecodings("0") == 0);
    assert(soln.numDecodings("1") == 1);
    assert(soln.numDecodings("00") == 0);
    assert(soln.numDecodings("01") == 0);
    assert(soln.numDecodings("10") == 1);
    assert(soln.numDecodings("12") == 2);
    assert(soln.numDecodings("27") == 1);
    assert(soln.numDecodings("123") == 3);  //(1,23), (12,3), (1,2,3)
    assert(soln.numDecodings("2412") == 4); //(2,4,1,2), (2,4,12), (24,1,2), (24,12)
    assert(soln.numDecodings("2212") == 5); //(2,2,1,2), (2,2,12), (2,21,2), (22,1,2),(22,12)
    assert(soln.numDecodings("1211") == 5);
}

int main(int argc, char** argv) {
    test_num_decodings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
