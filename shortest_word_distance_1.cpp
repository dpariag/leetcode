// Leetcode: https://leetcode.com/problems/shortest-word-distance/
// Given a list of words and two words w1 and w2, return the shortest distance between w1 and w2 in the list.

// Brute Force: Scan for each occurrence of w1, then scan forward looking for w2. O(n^2)
// Better: Scan the list storing indices of w1 and w2 in 2 vectors. Scan the two vectors in tandem to find the
// shortest distance.

// Acceptance: 56.6

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 16ms. Faster than 100.0% of submissions
class Solution {
public:
  int shortestDistance(const std::vector<std::string>& words, const std::string& word1, const std::string& word2) {
    std::vector<int> w1_indices, w2_indices;

    for (int i = 0; i < words.size(); ++i) {
      const auto& word = words[i];
      if (word == word1) {
        w1_indices.emplace_back(i);
      } else if (word == word2) {
        w2_indices.emplace_back(i);
      } 
    } // for

    int i = 0, j = 0;
    int shortest_distance = words.size(), distance = shortest_distance;

    while (i < w1_indices.size() && j < w2_indices.size()) {
      distance = std::abs(w1_indices[i] - w2_indices[j]);
      shortest_distance = std::min(shortest_distance, distance);
      if (w1_indices[i] < w2_indices[j]) {
        ++i;
      } else {
        ++j;
      }
    }
    return shortest_distance;        
  }
};

void test_shortest_distance() {
  Solution soln;
 
  assert(soln.shortestDistance(
    {"practice", "makes", "perfect", "coding", "makes"}, 
    "coding", "practice") == 3); 
  
  assert(soln.shortestDistance(
    {"practice", "makes", "perfect", "coding", "makes"}, 
    "makes", "coding") == 1); 
}

int main(int argc, char** argv) {
  test_shortest_distance();
  std::cout << argv[0] + 2 << "...OK!" << std::endl;
  return 0;
}
