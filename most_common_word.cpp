// Leetcode: https://leetcode.com/problems/most-common-word/

// Brute Force:
// Better:
// Acceptance: 41.1

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

using WordCounts = std::unordered_map<std::string, int>;
using Dictionary = std::unordered_set<std::string>;

// Accepted. 4ms. Faster than 100% of submissions.
class Solution {
public:
  std::string mostCommonWord(std::string paragraph, const std::vector<std::string>& banned) {
    WordCounts word_counts;
    Dictionary blacklist(banned.begin(), banned.end());

    int max = -1;
    std::string word, most_common;
    for (const auto& ch : paragraph) {
      if (std::isalpha(ch)) {
        word.push_back(std::tolower(ch));
      } else {
        if (!word.empty()) {
          std::cout << word << std::endl;
          if (blacklist.count(word) == 0) {
            auto count = ++word_counts[word];
            if (count > max) {
              max = count;
              most_common = word;
            }
          }
          word.clear();
        } // non-empty word
      } // else
    } // for
    if (!word.empty()) {
      std::cout << word << std::endl;
      if (blacklist.count(word) == 0) {
        auto count = ++word_counts[word];
        if (count > max) {
          max = count;
          most_common = word;
        }
      }
      word.clear();
    } // non-empty word
    return most_common;
  }
};

bool test_most_common(std::string paragraph, const std::vector<std::string> banned, std::string expected) {
  Solution soln;
  return soln.mostCommonWord(paragraph, banned) == expected; 
}

void test_most_common() {
  assert(test_most_common("Bob", {}, "bob")); 
  assert(test_most_common("Bob is a hitter. Bob hits. Bob hits!", {"bob"}, "hits")); 
  assert(test_most_common("Bob is a hitter. Bob hits. Bob hits!", {"is"}, "bob")); 
  assert(test_most_common("Bob is a hitter. Bob hits. Bob hits!", {"elephant", "xray"}, "bob")); 
  assert(test_most_common("Bob is a hitter. Bob hits. Bob hits a homer!", {"bob", "hits"}, "a")); 
}

int main(int argc, char** argv) {
  test_most_common();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
