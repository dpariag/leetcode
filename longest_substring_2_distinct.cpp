// Leetcode: https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/description/
// Given a string, find the length of the longest substring that contains <= 2 distinct characters.

// Brute Force: Generate all possible substrings, count distinct chars. O(n^3) time
// Better: Sliding window over the string counting distinct characters. O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 70.65% of submissions, ties 29.35% of submissions.
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(const std::string& s) {
        char first = '\0', second = '\0';
        int left = 0, right = 0, max_len = 0, first_count = 0, second_count = 0;
        
        while (right < s.size()) {
            char ch = s[right];
            if (first_count == 0) {
                first = ch;
                first_count = 1;
            } else if (ch == first) {
                ++first_count;
            } else if (second_count == 0) {
                second = ch;
                second_count = 1;
            } else if (ch == second) {
                ++second_count;
            } else {
                // Third character
                while (left < right && first_count > 0 && second_count > 0) {
                    if (s[left] == first) { --first_count; }
                    else if (s[left] == second) { --second_count; }
                    ++left;
                }
                continue; 
            }
            max_len = std::max(max_len, (right - left + 1));
            ++right;
        }
        return max_len;
    }
};

void test_longest_distinct() {
    Solution soln;

    assert(soln.lengthOfLongestSubstringTwoDistinct("abcdd") == 3);
    assert(soln.lengthOfLongestSubstringTwoDistinct("eceba") == 3);
    assert(soln.lengthOfLongestSubstringTwoDistinct("aaaaaa") == 6);
    assert(soln.lengthOfLongestSubstringTwoDistinct("aaaaaab") == 7);
    assert(soln.lengthOfLongestSubstringTwoDistinct("aababaaab") == 9);
    assert(soln.lengthOfLongestSubstringTwoDistinct("bacbcccccc") == 8);
}

int main(int argc, char** argv) {
    test_longest_distinct();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
