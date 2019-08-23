// Leetcode: https://leetcode.com/problems/shortest-word-distance-ii/

// Brute Force:
// Better:
// Acceptance: 

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 44ms. Faster than 81.04% of cpp submissions.
class WordDistance {
public:
  WordDistance(const std::vector<std::string>& words) {
    for (int i = 0; i < words.size(); ++i) {
      const auto& word = words[i];
      word_indices[word].emplace_back(i); 
    }
  }

  int shortest(const std::string& word1, const std::string& word2) {
    int distance = word_indices.size();
    int min_distance = distance;
    const auto& word1_indices = word_indices[word1];
    const auto& word2_indices = word_indices[word2];

    int i = 0, j = 0;
    int w1_idx = i, w2_idx = j;
    while (i < word1_indices.size() || j < word2_indices.size()) {
      w1_idx = std::min(i, int(word1_indices.size() - 1));
      w2_idx = std::min(j, int(word2_indices.size() - 1));
      distance = std::abs(word1_indices[w1_idx] - word2_indices[w2_idx]);
      min_distance = std::min(min_distance, distance);
      if (i < word1_indices.size() && word1_indices[w1_idx] < word2_indices[w2_idx]) {
        ++i;
      } else if (j < word2_indices.size() && word2_indices[w2_idx] < word1_indices[w1_idx]) { 
        ++j;
      } else {
        break;
      }
    }
    return min_distance;
  }

private:
  std::unordered_map<std::string, std::vector<int>> word_indices;
};

void test_word_distance() {
  WordDistance d1({"practice", "makes", "perfect", "coding", "makes"});
  assert(d1.shortest("coding", "practice") == 3);
  assert(d1.shortest("coding", "makes") == 1);
  assert(d1.shortest("makes", "coding") == 1);
  
  WordDistance d2({"a", "a", "b", "b"});
  assert(d2.shortest("a", "b") == 1);
  assert(d2.shortest("b", "a") == 1);
}

int main(int argc, char** argv) {
  test_word_distance();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
