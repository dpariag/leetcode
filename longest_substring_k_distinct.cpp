// Leetcode: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/description/

// Brute Force: Generate all substrings, count distinct in each, track longest. O(n^3) time.
// Better: Use a sliding window (left and right indices) to iterate the string. 
// Grow the window while it contains k or fewer distinct chars, shrink it otherwise. O(n) time and O(1) space.

#include <string>
#include <iostream>
#include <assert.h>

// Start: 2:43pm. Coded: 2:51pm
// Accepted. 6ms. Beats 69.69% of submissions, ties 30.31% of submissions.
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k) {
        int left = 0, right = 0, num_distinct = 0, max_len = 0;
        int counts[255] = {0};

        while (right < int(s.size())) {
            while (right < s.size() && num_distinct <= k) {
                ++counts[s[right]];
                if (counts[s[right]] == 1) { ++num_distinct; } // new char
                if (left <= right && num_distinct <= k) {
                    max_len = std::max(max_len, (right - left + 1));
                }
                ++right;
            }

            while (left <= right && num_distinct > k) {
                --counts[s[left]];
                if (counts[s[left]] == 0) { --num_distinct; } // no more of s[left] in the window
                ++left;
            }
        }
        return max_len;
    }
};

void test_longest_substring() {
    Solution soln;
    
    assert(soln.lengthOfLongestSubstringKDistinct("eceba", 2) == 3);
    assert(soln.lengthOfLongestSubstringKDistinct("aaaaaaa", 1) == 7);
    assert(soln.lengthOfLongestSubstringKDistinct("abababab", 2) == 8);
    assert(soln.lengthOfLongestSubstringKDistinct("ababcabab", 2) == 4);
    assert(soln.lengthOfLongestSubstringKDistinct("ababcabab", 1) == 1);
    assert(soln.lengthOfLongestSubstringKDistinct("abcdefgh", 3) == 3);
    assert(soln.lengthOfLongestSubstringKDistinct("abaaacccaaxx", 2) == 8);
    assert(soln.lengthOfLongestSubstringKDistinct("abaaacccaaxx", 3) == 10);
}

int main(int argc, char** argv) {
    test_longest_substring();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
