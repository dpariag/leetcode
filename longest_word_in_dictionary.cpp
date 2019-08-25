// Leetcode: https://leetcode.com/problems/longest-word-in-dictionary/

// Brute Force: For every word, recursively search for successively smaller prefixes in the input list. O(n^2*len(w)):
// Better: Store words in a hash map and cache the results of earlier searches. O(n) time.
// Acceptance: 45.5%

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

enum class Status {
  eUnknown = 0,
  eBuildable = 1,
  eNotBuildable = 2
};

using WordStatus = std::unordered_map<std::string, Status>;  

// Accepted. 44ms. Faster than 94.70% of C++ submissions
class Solution {
public:
  bool dfs(WordStatus& word_status, const std::string& word) {
    if (word.empty()) { return true; }

    auto found = word_status.find(word);
    if (found == word_status.end()) { return false; }
    if (found->second != Status::eUnknown) {
      return (found->second == Status::eBuildable);
    }

    // Haven't processed this word before
    std::string prefix(word, 0, word.size() - 1);
    if (dfs(word_status, prefix)) {
      found->second = Status::eBuildable;
      return true;
    }
    found->second = Status::eNotBuildable;
    return false;
  }

  std::string longestWord(std::vector<std::string>& words) {
    WordStatus word_status;
    for (const auto& word : words) {
      word_status.emplace(std::move(word), Status::eUnknown);
    }
    std::string longest;
    for (const auto& item : word_status) {
      if (dfs(word_status, item.first)) {
        if (item.first.size() > longest.size() || 
            (item.first.size() == longest.size() && item.first < longest)) {
          longest = item.first;
        }
      }
    }
    return longest;
  }
};

bool test_longest_word(std::vector<std::string> words, std::string expected) {
  Solution soln;
  return soln.longestWord(words) == expected;
}

void test_longest_word() {
  assert(test_longest_word({"w","wo","wor","worl", "world"}, "world"));
  assert(test_longest_word({"a", "banana", "app", "appl", "ap", "apply", "apple"}, "apple"));
  assert(test_longest_word({"a", "banana", "app", "appl", "ap", "apply", "appstore"}, "apply"));
  assert(test_longest_word({"b", "ban", "app", "appl", "ap", "apply", "appstore", "ba"}, "ban"));
}

int main(int argc, char** argv) {
  test_longest_word();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
