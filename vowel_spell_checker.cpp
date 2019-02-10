// Leetcode: https://leetcode.com/problems/vowel-spellchecker/
// Given a wordlist, we want to implement a spellchecker that converts a query word into a corrected version.

// Brute Force: For each query, iterate word list to match exactly/capitlization/vowel exchange. O(n*m)
// Better: Build 3 hash maps for exact/capitalization/vowel matching. O(n) time
// Acceptance: 38.7

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <cctype>

using WordList = std::vector<std::string>;
using WordMap = std::unordered_map<std::string, int>; // string -> index in word list

// Accepted. 96ms. Faster than 100% of cpp submissions.
class Solution {
public:
  bool is_vowel(char ch) {
    ch = std::tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
  }

  std::string replace_vowels(const std::string& s) {
    std::string result;
    result.reserve(s.size());
    for (const auto ch : s) {
      result.append(1, (is_vowel(ch) ? '-' : std::tolower(ch)));
    }
    return result;
  }

  std::string to_lower(const std::string& s) {
    std::string result;
    result.reserve(s.size());
    for (const auto ch : s) {
      result.append(1, std::tolower(ch));
    }
    return result; 
  }

  WordList spellchecker(WordList& wordlist, WordList& queries) {
    WordMap exact_matches(wordlist.size() * 2);
    for (int i = 0; i < wordlist.size(); ++i) {
      exact_matches.emplace(wordlist[i], i);  // doesn't replace duplicates
    }

    WordMap capital_matches(wordlist.size() * 2); 
    for (int i = 0; i < wordlist.size(); ++i) {
      capital_matches.emplace(to_lower(wordlist[i]), i); // doesn't replace duplicates 
    }

    WordMap vowel_matches(wordlist.size() * 2);
    for (int i = 0; i < wordlist.size(); ++i) {
      vowel_matches.emplace(replace_vowels(wordlist[i]), i); // doesn't replace duplicates
    }

    WordList corrected;
    corrected.reserve(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      const auto& query = queries[i];
      auto found = exact_matches.find(query);
      if (found != exact_matches.end()) {
        corrected.emplace_back(wordlist[found->second]);
        continue;
      }

      found = capital_matches.find(to_lower(query));
      if (found != capital_matches.end()) {
        corrected.emplace_back(wordlist[found->second]);
        continue;
      }
      
      found = vowel_matches.find(replace_vowels(query));
      if (found != vowel_matches.end()) {
        corrected.emplace_back(wordlist[found->second]);
        continue;
      }
      corrected.emplace_back("");
    }
    return corrected;
  }
};

bool test_spell_checker(WordList words, WordList queries, WordList expected) {
  Solution soln;
  auto corrected = soln.spellchecker(words, queries);
  std::sort(corrected.begin(), corrected.end());
  std::sort(expected.begin(), expected.end());
  return corrected == expected;
}
  

void test_spell_checker() {
  assert(test_spell_checker(
  {"KiTe","kite","hare","Hare"},
  {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"}, 
  {"kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"}));
}

int main(int argc, char** argv) {
  test_spell_checker();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
