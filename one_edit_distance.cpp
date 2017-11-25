// Leetcode: https://leetcode.com/problems/one-edit-distance/description/
// Given two strings S and T, determine if they are both one edit distance apart.

// Brute Force: Perform all possible edits to s, t and compare equality. O(n^2) time.
// Better: Compare lengths. Scan strings allowing one substitution for same length strings, 
// and one insert/remove for strings of different lengths. O(n) time.

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 21.02% of submissions, ties 78.98% of submissions.
class Solution {
public:
    inline bool one_edit_same_len(const std::string& s, const std::string& t) {
        bool mismatch = false;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != t[i]) {
                if (!mismatch) { mismatch = true; } 
                else { return false; }
            }
        }
        return mismatch;
    }

    inline bool one_edit_diff_len(const std::string& s, const std::string& t) {
        if (std::abs(int(s.length() - t.length())) > 1) { return false; }

        int li = 0, si = 0;
        bool skip = false;
        const auto& longer = (s.length() > t.length()) ? s : t;
        const auto& shorter = (s.length() < t.length()) ? s : t;
        while (li < longer.length() && si < shorter.length()) {
            if (longer[li] != shorter[si]) {
                if (!skip) {
                    skip = true;
                    ++li;
                    continue;
                } else {
                    return false;
                }
            }
            ++li, ++si;
        }
        return skip || (li == longer.size() - 1);
    }

    bool isOneEditDistance(const std::string& s, const std::string& t) {
        if (s.length() == t.length()) {
            return one_edit_same_len(s, t);
        }
        return one_edit_diff_len(s, t);
    }
};

void test_one_edit_distance() {
    Solution soln;

    assert(soln.isOneEditDistance("hello", "hell") == true);
    assert(soln.isOneEditDistance("hall", "shall") == true);
    assert(soln.isOneEditDistance("hall", "hell") == true);
    assert(soln.isOneEditDistance("shall", "hell") == false);
    assert(soln.isOneEditDistance("halt", "melt") == false);
    assert(soln.isOneEditDistance("melted", "melt") == false);
    assert(soln.isOneEditDistance("melt", "melted") == false);
    assert(soln.isOneEditDistance("melt", "melt") == false);
}

int main(int argc, char** argv) {
    test_one_edit_distance();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
