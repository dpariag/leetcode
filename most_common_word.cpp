// Leetcode: https://leetcode.com/problems/most-common-word/

// Approach: Scan a word, count it and track the highest cardinality word.
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

    int i = 0, max = -1;
    std::string word, most_common;
    while (i < paragraph.size()) {
      // Skip non alphanumeric
      while(i < paragraph.size() && !std::isalpha(paragraph[i])) { ++i; }
      // Build a word
      while(i < paragraph.size() && std::isalpha(paragraph[i])) {
        word.push_back(std::tolower(paragraph[i]));
        ++i;
      }
      // Check word against the blacklist
      if (!word.empty()) {
        if (blacklist.count(word) == 0) {
          auto count = ++word_counts[word];
          if (count > max) {
            max = count;
            most_common = word;
          }
        }
        word.clear();
      }
    } // while
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
