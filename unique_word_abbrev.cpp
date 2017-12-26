// Leetcode: https://leetcode.com/problems/unique-word-abbreviation/description/
// A word's abbreviation is of the form <first letter><number><last letter> (e.g., dog -> d1g)
// Given a dictionary, determine if a given word is either
// 1) Not in the dictionary and neithe is it's abbreviation
// 2) In the dictionary, but with a unique abbreviation.

// Brute Force: For each word, scan the dictionary constructing abbreviations and checking for uniqueness.
// Better: Store dictionary in and unordered_set and abbreviaton counts in a hash map.

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using Dictionary = std::unordered_set<std::string>;
using Counts = std::unordered_map<std::string, int>; // abbreviation -> count

// Accepted. 139ms. Beats 64.71% of submissions, ties 3.78% of submissions.
class ValidWordAbbr {
public:
    ValidWordAbbr(const Words& words): m_dict(words.size()*2), m_counts(words.size()*2) {
        for (auto& w : words) {
            if (m_dict.count(w) > 0) continue;  // Only count the word once
            auto abbrev = make_abbrev(w);
            m_counts[abbrev]++;
            m_dict.emplace(w);
        }
    }

    bool isUnique(const std::string& word) {
        auto abbrev = make_abbrev(word);
        auto found = m_counts.find(abbrev);
        int abbrev_count = (found == m_counts.end()) ? 0 : found->second;
        int dict_count = m_dict.count(word);
        return  (dict_count == 0 && abbrev_count == 0) ||   // Neither word nor abbrev is in dictionary
                (dict_count == 1 && abbrev_count == 1);     // Word is in dict, and abbrev is unique.
    }

private:
    inline std::string make_abbrev(const std::string& w) {
        if (w.size() <= 2) { return w; } 
        std::string abbrev;
        abbrev.append(1, w.front());
        abbrev.append(std::to_string(w.size() - 2));
        abbrev.append(1, w.back());
        return abbrev;
    }

    Dictionary m_dict;
    Counts m_counts;
};

bool test_is_unique(Words words, std::string word, bool expected) {
    ValidWordAbbr v(words);
    return v.isUnique(word) == expected;
}

void test_is_unique() {
    assert(test_is_unique({}, "", true));
    assert(test_is_unique({}, "hello", true));
    assert(test_is_unique({"dog", "cake", "card"}, "dog", true));
    assert(test_is_unique({"dog", "dog", "card"}, "dog", true));    // Duplicates counted once
    assert(test_is_unique({"", "door", "cake", "card"}, "", true));
    assert(test_is_unique({"dr", "door", "cake", "card"}, "dr", true));
    assert(test_is_unique({"deer", "door", "cake", "card"}, "dear", false));
    assert(test_is_unique({"deer", "door", "cake", "card"}, "cart", true));
    assert(test_is_unique({"deer", "door", "cake", "card"}, "cane", false));
    assert(test_is_unique({"deer", "door", "cake", "card"}, "make", true));
}

int main(int argc, char** argv) {
    test_is_unique();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
