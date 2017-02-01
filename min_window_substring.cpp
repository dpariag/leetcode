// Leetcode: https://leetcode.com/problems/minimum-window-substring/
// Given a string S and a string T, find the minimum window in S which will contain all the 
// characters in T in complexity O(n).
// Example: S = "ADOBECODEBANC", T = "ABC", return "BANC".

// Brute Force: Generate all substrings of S, check if each covers T. O(n^3) time and O(n) space.
// Better: Use two hash_maps and a sliding window over S.

#include <string>
#include <iostream>
#include <unordered_map>
#include <assert.h>

class CharSet {
public:
    CharSet(const std::string& s) : num_covered(0) {
        for (auto ch : s) {
            to_cover[ch]++;
        }
    }

    inline void add(char ch) {
        auto found = to_cover.find(ch);
        if (found != to_cover.end()) {
            auto count = ++covered[ch];
            if (count == found->second) { ++num_covered; }
        }
    }

    inline void remove(char ch) {
        auto found = covered.find(ch);
        if (found != covered.end() && found->second > 0) {
            if (found->second == to_cover[ch]) { --num_covered; }
            --found->second;
        }
    }

    inline bool covers() const {
        return num_covered == to_cover.size();
    }

private:
    int num_covered;
    std::unordered_map<char, int> to_cover;
    std::unordered_map<char, int> covered;
};

struct Window {
    int start = 0;
    int end = -1;
    int size() const { return (end - start) + 1; }
};

// 59ms. Beats 35.73% of submissions, ties 0.91% of submissions.
class Solution {
public:
    std::string minWindow(const std::string& s, const std::string& t) {
        if (t.empty()) { return std::string();}
        Window min_window, cur_window;
        CharSet charset(t);

        while (cur_window.end < int(s.size())) {
            while (charset.covers()) {
                if (min_window.size() == 0 || cur_window.size() < min_window.size()) {
                    min_window = cur_window;
                }
                charset.remove(s[cur_window.start]);
                ++cur_window.start; 
            }
            ++cur_window.end;
            charset.add(s[cur_window.end]);
        }
        return s.substr(min_window.start, min_window.size()); 
    }
};

bool test_min_window(const std::string& s, const std::string& t, const std::string& expected) {
    Solution soln;
    auto result = soln.minWindow(s,t);
    return result == expected;
}

void test_min_window() {
    assert(test_min_window("ADOBECODEBANC", "DOB", "DOB"));
    assert(test_min_window("ADOBECODEBANC", "ABC", "BANC"));
    assert(test_min_window("QWERTY", "WT", "WERT"));
    assert(test_min_window("ABACADAEAF", "ABC", "BAC"));
    assert(test_min_window("AAAAAA", "AAAA", "AAAA"));
    assert(test_min_window("AAAAAA", "", ""));
    assert(test_min_window("XXYYXXZNOPXZPPY", "XYZ", "YXXZ"));
}

int main(int argc, char** argv) {
    test_min_window();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
