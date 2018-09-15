// Leetcode: https://leetcode.com/problems/stickers-to-spell-word/description/
//

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <unordered_map>
#include <assert.h>

using Cache = std::unordered_map<std::string, int>;

struct Sticker {
  Sticker(const std::string& str): word(str), counts(26, 0) {
    for (auto ch : str) {
      counts[ch-'a']++;
    }
  }

  std::string get_next_target(const std::string& str) {
    auto temp_counts = counts;
    std::string next;
    for (auto ch : str) {
      if (temp_counts[ch-'a'] == 0) {
        next.push_back(ch);
      } else {
        --temp_counts[ch-'a'];
      }
    }
    return next;
  }
  std::string word;
  std::vector<int> counts; // count of each letter
};

// Accepted. 232ms. Beats 23.85% of submissions.
class Solution {
public:
  int dfs(std::vector<Sticker>& stickers, Cache& cache, std::string& target) {
    if (target.empty()) { return 0; }

    // Check the cache to see if we've searched this target already
    auto found = cache.find(target);
    if (found != cache.end()) { return found->second; }

    int min_stickers = -1;
    for (int i = 0; i < stickers.size(); ++i) {
      auto next_target = stickers[i].get_next_target(target);
      if (next_target.size() != target.size()) {
        auto num_stickers = dfs(stickers, cache, next_target);
        if (num_stickers >= 0) {
          min_stickers = (min_stickers == -1) ? 
            1 + num_stickers : 
            std::min(min_stickers, 1 + num_stickers);
        }
      }
    }
    cache[target] = min_stickers;
    return min_stickers;
  }

  int minStickers(std::vector<std::string>& sticker_words, std::string& target) {
    Cache cache;
    std::vector<Sticker> stickers;

    for (const auto& word : sticker_words) {
      stickers.emplace_back(Sticker(word));
    }
    auto min_stickers = dfs(stickers, cache, target);
    return min_stickers;
  }
};

bool test_min_stickers(std::vector<std::string> words, std::string target, int expected) {
  Solution soln;
  return soln.minStickers(words, target) == expected;
}

void test_min_stickers() {
  assert(test_min_stickers({"cat", "puppy", "bat", "mice", "rat"}, "bear", 3));
  assert(test_min_stickers({"cat", "pear", "bat"}, "bear", 2));
  assert(test_min_stickers({"with", "example", "science"}, "thehat", 3));
  assert(test_min_stickers({"notice", "possible"}, "basicbasic", -1));
}

int main(int argc, char** argv) {
  test_min_stickers();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
