// Leetcode: https://leetcode.com/problems/prefix-and-suffix-search/description/
// Given an array, words[i] has weight i.
// Design a WordFilter class that has a single method f(prefix, suffix)
// which returns the highest weight word containing 'prefix' as a prefix and 'suffix' as a suffix. 

// Approach: Build a hash map containing indices of words matching a particular prefix/suffix

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Words = std::vector<std::string>;
using PrefixMap = std::unordered_map<std::string, std::vector<int>>;

// Accepted. 212ms. Beats 96.81% of submissions.
class WordFilter {
public:
  WordFilter(const Words& words) {
    for (int i = words.size() - 1; i >= 0; --i) {
      const auto& word = words[i];
      for (int len = 0; len <= word.size(); ++len) {
        auto prefix = word.substr(0, len);
        prefixes[prefix].emplace_back(i);

        auto suffix = word.substr(word.size() - len, len);
        suffixes[suffix].emplace_back(i);
      }
    }
  }

  int f(const std::string& prefix, const std::string& suffix) {
    const auto& prefix_list = prefixes[prefix];
    const auto& suffix_list = suffixes[suffix];
    int i = 0, j = 0;
    while (i < prefix_list.size() && j < suffix_list.size()) {
      if (prefix_list[i] == suffix_list[j]) {
        return prefix_list[i];
      } else if (prefix_list[i] > suffix_list[j]) {
        ++i;
      } else {
        ++j;
      }
    }
    return -1;
  }

private:
  PrefixMap prefixes;
  PrefixMap suffixes;
};

void test_word_filter() {
  WordFilter wf({"apple", "argue", "ape", "api", "ppe"});
  assert(wf.f("a", "e") == 2);
}

int main(int argc, char** argv) {
  test_word_filter();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
