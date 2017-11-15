// Leetcode: https://leetcode.com/problems/find-all-anagrams-in-a-string/description/
// Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

// Brute Force: Generate all substrings of length p.size() in s, and compare character counts
// against p. O(len(s) * len(p))
// Better: Scan s counting chars in a sliding window of the last p.size() chars. O(len(s)) time.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using CharCount = std::unordered_map<char,int>;

// Accepted. 66ms. Beats 19.08% of submissions, ties 1.05% of submissions.
class Solution {
public:
    std::vector<int> findAnagrams(std::string s, std::string p) {
        std::vector<int> result;
        CharCount p_count, window_count;

        for (auto ch : p) { p_count[ch]++; }
       
        int num_equal = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto new_count = ++window_count[s[i]];
            auto old_count = new_count - 1;
            auto in_p = p_count.find(s[i]);
            if (in_p != p_count.end()) {
                if (in_p->second == new_count) { ++num_equal; }
                else if (in_p->second == old_count) { --num_equal; }
            }

            if (i >= p.size()) {
                new_count = --window_count[s[i-p.size()]];
                old_count = new_count + 1;
                in_p = p_count.find(s[i-p.size()]);
                if (in_p != p_count.end()) {
                    if (in_p->second == new_count) { ++num_equal; }
                    else if (in_p->second == old_count) { --num_equal; }
                }
                if (new_count == 0) {
                    window_count.erase(s[i-p.size()]);
                }
            }

            if (num_equal == p_count.size() && window_count.size() == p_count.size()) {
                result.emplace_back(i - p.size() + 1);
            } 
        }
        return result; 
    }
};

void test_find_all_anagrams() {
    Solution soln;

    assert(soln.findAnagrams("abab", "ab") == std::vector<int>({0,1,2}));
    assert(soln.findAnagrams("cbaebabacd", "abc") == std::vector<int>({0,6}));
    assert(soln.findAnagrams("aaaaa", "aa") == std::vector<int>({0,1,2,3}));
    assert(soln.findAnagrams("aaaaa", "ab") == std::vector<int>({}));
    assert(soln.findAnagrams("aabaa", "ab") == std::vector<int>({1,2}));
    assert(soln.findAnagrams("aabaa", "aba") == std::vector<int>({0,1,2}));
    assert(soln.findAnagrams("xyzxyz", "zyx") == std::vector<int>({0,1,2,3}));
}

int main(int argc, char** argv) {
    test_find_all_anagrams();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
