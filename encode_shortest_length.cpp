// Leetcode: https://leetcode.com/problems/encode-string-with-shortest-length/description/
// Given a non-empty string, encode the string such that its encoded length is the shortest.
// The encoding rule is: k[encoded_string], where encoded_string is repeated exactly k times.

// Approach: Use dynamic programming to build table[i][j] = {shortest abbreviation for s[i..j]}
// Then table[i][j] is computed by considering every split of s[i..j] into two substrings
// and looking at their abbreviations combined.

#include <vector>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<std::string>>;

// Accepted. 108ms. Beats 11.64% of submissions, ties 0.68% of submissions.
class Solution {
public:
    // Return the number of times that b can be repeated to build a
    inline int repeats(const std::string& a, const std::string& b) {
        int rem = a.size() % b.size(); 
        if (rem != 0) { return 0; }

        int times = a.size() / b.size();
        std::string str;
        str.reserve(a.size());
        for (int i = 0; i < times; ++i) { str.append(b); }
        return str == a ? times : 0;
    }

    inline std::string build_abbrev(int times, const std::string& s) {
        std::string abbrev = std::to_string(times);
        abbrev.append(1, '[');
        abbrev.append(s);
        abbrev.append(1, ']');
        return abbrev;
    }

    inline std::string concat(const std::string& abbrev1, const std::string& abbrev2) {
        std::string result;
        result.reserve(abbrev1.size() + abbrev2.size());
        if (abbrev1 == abbrev2) {
            result.append("2[");
            result.append(abbrev1);
            result.append(1, ']');
            return result;
        }
        result.append(abbrev1);
        result.append(abbrev2);
        return result;
    }


    std::string encode(const std::string& s) {
        if (s.empty()) { return s; }
        Table table(s.size(), std::vector<std::string>(s.size()));
        
        for (int len = 1; len <= s.size(); ++len) {
            for (int start = 0; start+len-1 < s.size(); ++start) {
                int end = start + len - 1;
                auto str = s.substr(start, len);
                if (len <= 3) { 
                    table[start][end] = str; 
                } else {
                    std::string abbrev = str;
                    for (int k = 1; k < str.size(); ++k) {
                        std::string left = str.substr(0, k);
                        int times = repeats(str, left);
                        if (times > 0) {
                            auto repeat_abbrev = build_abbrev(times, left);
                            if (repeat_abbrev.size() <= abbrev.size()) {
                                abbrev = repeat_abbrev;
                            }
                        }
                        auto concat_abbrev = concat(table[start][start+k-1], table[start+k][end]);
                        if (concat_abbrev.size() <= abbrev.size()) {
                            abbrev = concat_abbrev;
                        }
                    }
                    table[start][end] = abbrev;
                }
            }
        }
        auto& abbrev = table[0].back();
        return abbrev.size() < s.size() ? abbrev : s; 
    }
};

bool test_encode(std::string s, std::string expected) {
    Solution soln;
    auto encoded = soln.encode(s);
    return encoded == expected;
}

void test_encode() {
    assert(test_encode("aa", "aa"));
    assert(test_encode("a", "a"));
    assert(test_encode("aaa", "aaa"));
    assert(test_encode("aaaaa", "5[a]"));
    assert(test_encode("xbcdbcdbcd", "x3[bcd]"));
    assert(test_encode("abbbabbbcabbbabbbc", "2[2[abbb]c]"));
}

int main(int argc, char** argv) {
    test_encode();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
