// Leetcode: https://leetcode.com/problems/minimum-window-subsequence/description/
// Given strings S and T, find the minimum (contiguous) substring of S, so that has T as a subsequence.

// Brute Force: Generate all substrings of S, check if T is contained. O(n^2*m) time.
// Better: Scan from each index in S to see if T can be contained. O(n^2) time.
// Even Better: DP approach. Let T[i][j] = {rightmost starting index in S which contains T[0..j] }
// Then T[i][j] = (S[i-1] == T[j-1]) ? T[i-i][j-1] : T[i][j-1]

#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<int>>;

// Accepted. 102ms. Beats 48.23% of submissions, ties 2.13% of submissions.
class Solution {
public:
    std::string minWindow(const std::string& s, const std::string& t) {
        Table table(t.size()+1, std::vector<int>(s.size()+1, -1));

        for (int i = 0; i <= s.size(); ++i) { table[0][i] = i; }

        for (int i = 1; i <= t.size(); ++i) {
            for (int j = 1; j <= s.size(); ++j) {
                if (t[i-1] == s[j-1]) {
                    table[i][j] = table[i-1][j-1];
                } else {
                    table[i][j] = table[i][j-1];
                }
            }
        }

        int last_start = -1, last_end = -1;
        int min_len = s.size() + 1;
        for (int i = 0; i <= s.size(); ++i) {
            auto start = table[t.size()][i];
            if (start != -1) {
                if (i-start < min_len) {
                    last_start = start; 
                    last_end = i-1;
                    min_len = i-start;
                }
            }
        }
        return last_start == -1 ? "" : s.substr(last_start, last_end-last_start+1);
    }
};

void test_min_window() {
    Solution soln;

    assert(soln.minWindow("cababaabb", "aabb") == "aabb");
    assert(soln.minWindow("abcdebdde", "bde") == "bcde");
    assert(soln.minWindow("fgrqsqsnodwmxzkzxwqegkndaa", "fnok") == "fgrqsqsnodwmxzk");
    assert(soln.minWindow("nkzcnhczmccqouqadqtmjjzltgdzthm", "bt") == "");
}

int main(int argc, char** argv) {
    test_min_window();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
