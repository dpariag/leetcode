// Leetcode: https://leetcode.com/problems/anagrams/ 
// Given an array of strings, group anagrams together.
// Example: Given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
// Return: [ ["ate", "eat","tea"], ["nat","tan"], ["bat"] ]

// Brute Force: For each word, check if it is an anagram of any other word (e.g., by sorting
// or counting charactes). O(n^3) time.
// Better: Iterate words, sorting each word, and collecting words with the same sorted form.
// Avoid string copies wherever possible. O(n*m*log(m)) where there are n words of length m.

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Strings = std::vector<std::string>;
using Groups = std::vector<Strings>;
using AnagramGroups = std::unordered_map<std::string, Strings>;

// Accepted: 46ms. Beats 89.05% of submissions, ties 2.03% of submissions.
class Solution {
public:
    Groups groupAnagrams(const Strings& strs) {
        AnagramGroups anagram_groups;

        for (auto& s : strs) {
            auto key = s;
            std::sort(key.begin(), key.end()); 
            anagram_groups[key].emplace_back(s);
        }

        Groups groups;
        for (auto& ag : anagram_groups) {
            groups.emplace_back(std::move(ag.second));
        }
        return groups;
    }
};

void sort_groups(Groups& groups) {
    for (auto& group : groups) {
        std::sort(group.begin(), group.end());
    }
    std::sort(groups.begin(), groups.end());
}

bool test_group_anagrams(const Strings& strings, Groups expected) {
    Solution soln;

    auto result = soln.groupAnagrams(strings);
    sort_groups(result);
    sort_groups(expected);
    return result == expected;
}

void test_group_anagrams() {
    assert(test_group_anagrams({}, {}));
    assert(test_group_anagrams({"tea"}, {{"tea"}}));
    assert(test_group_anagrams({"tea", "hat"}, {{"hat"}, {"tea"}}));
    assert(test_group_anagrams({"tea", "hat", "eat"}, {{"hat"}, {"eat", "tea"}}));
    assert(test_group_anagrams({"ate", "tea", "hat", "eat"}, {{"hat"}, {"eat", "tea", "ate"}}));
    assert(test_group_anagrams({"tar", "ate", "tea", "rat", "eat"}, {{"rat", "tar"}, 
                                {"eat", "tea", "ate"}}));
}

int main(int argc, char** argv) {
    test_group_anagrams();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
