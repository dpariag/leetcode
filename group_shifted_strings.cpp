// Leetcode: https://leetcode.com/problems/group-shifted-strings/description/
// Given a string, we can "shift" each of its letter to its successive letter, (e.g., "abc" -> "bcd"). 
// We can keep "shifting" which forms the sequence: "abc" -> "bcd" -> ... -> "xyz"
// Given a list of strings (lowercase letters), group all strings that belong to the same shift sequence.

// Brute Force: For each string, generate it's shift sequence checking if each new string is in the list.
// Better: Build a shift key for each string, and group strings by shift key. O(n) time.

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;
using Groups = std::unordered_map<std::string, Strings>;

// Accepted. 3ms. Beats 36.46% of submissions, ties 63.54% of submissions
class Solution {
public:

    std::string build_shift_key(const std::string& s) {
        if (s.empty()) return s;
        std::string key;
        char prev = s.front();
        for (auto ch : s) {
            int diff = ch - prev;
            if (diff < 0) diff = 26 + diff;
            char to_append = 'a' + diff;
            key.append(1, to_append);
            prev = ch;
        }
        return key;
    }

    std::vector<Strings> groupStrings(Strings& strings) {
        Groups groups;
        for (auto& s : strings) {
            auto key = build_shift_key(s);
            groups[key].emplace_back(s);
        }

        std::vector<Strings> result;
        for (auto iter = groups.begin(); iter != groups.end();) {
            result.emplace_back(std::move(iter->second));
            auto to_erase = iter++;
            groups.erase(to_erase);
        }
        return result;
    }
};

bool test_group_strings(Strings strings, std::vector<Strings> expected) {
    for (auto& e : expected) {
        std::sort(e.begin(), e.end());
    } 
    std::sort(expected.begin(), expected.end());

    Solution soln;
    auto result = soln.groupStrings(strings);
    for (auto& r : result) {
        std::sort(r.begin(), r.end());
    }
    std::sort(result.begin(), result.end());
    return result == expected;
}

void test_group_strings() {
    assert(test_group_strings({"a", "z"}, {{"a","z"}}));
    assert(test_group_strings({"a", "ab", "z", "bc"}, {{"a","z"}, {"ab", "bc"}}));
    assert(test_group_strings({"a", "aa", "z", "bb", "y"}, {{"a","y","z"}, {"aa", "bb"}}));
    assert(test_group_strings({"abc","bcd","acef","xyz","az","ba","a","z"}, {{"acef"},{"a","z"},{"abc","bcd","xyz"},{"az","ba"}}));
    assert(test_group_strings({"a", "aa", "z", "bb", "y", "acef"}, {{"a","y","z"}, {"aa", "bb"}, {"acef"}}));
}

int main(int argc, char** argv) {
    //Solution s;
    //std::cout << (-1 % 26) << std::endl;
    //std::cout << s.build_shift_key("az") << std::endl;
    //std::cout << s.build_shift_key("ba") << std::endl;
    test_group_strings();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
