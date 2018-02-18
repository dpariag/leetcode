// Leetcode: https://leetcode.com/problems/top-k-frequent-words/description/
// Given a non-empty list of words, return the k most frequent elements, sorted by 
// frequency from highest to lowest, breaking ties by alphabetical order.

// Approach: Use a hash map to count words, then a min heap to track the top k.
// Be careful about how ties are broken.

#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using Counts = std::unordered_map<std::string, int>;

struct WordCount {
    std::string word;
    int count = 0;
    bool operator>(const WordCount& other) const {
        if (count == other.count) { return word < other.word; }
        return count > other.count;
    }
    WordCount(const std::string& w, int c): word(w), count(c){}
};
using MinHeap = std::priority_queue<WordCount, std::vector<WordCount>, std::greater<WordCount>>;

// Accepted. 15ms. Beats 73.89% of submissions, ties < 7.60% of submissions.
class Solution {
public:
    Words topKFrequent(Words& words, int k) {
        Counts counts(words.size()*2);
        for (auto& w : words) { counts[w]++; }

        MinHeap top_k;
        for (auto c : counts) {
            if (top_k.size() < k) {
                top_k.emplace(c.first, c.second);
            } else {
                auto& top = top_k.top();
                if (c.second > top.count || (c.second == top.count && c.first < top.word)) {
                    top_k.pop();
                    top_k.emplace(c.first, c.second);
                }
            }
        }

        Words result;
        for (int i = 0; i < k && !top_k.empty(); ++i) {
            result.emplace_back(top_k.top().word);
            top_k.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

bool test_topk_frequent(Words words, int k, Words expected) {
    Solution soln;
    auto top_k = soln.topKFrequent(words, k);
    return top_k.size() == k && top_k == expected;
}

void test_topk_frequent() {
    assert(test_topk_frequent({"i", "love", "leetcode", "i", "love", "coding"}, 2, {"i", "love"}));
    assert(test_topk_frequent({"i","i", "i", "i"}, 1, {"i"}));
    assert(test_topk_frequent({"i","i", "i", "jump", "to", "to"}, 2, {"i", "to"}));
    assert(test_topk_frequent({"i","i", "to", "jump", "to", "to"}, 2, {"to", "i"}));
    assert(test_topk_frequent({"i","i", "to", "jump", "hi", "hi"}, 3, {"hi", "i", "jump"}));
    assert(test_topk_frequent({"the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"}, 4, 
           {"the", "is", "sunny", "day"}));
}

int main(int argc, char** argv) {
    test_topk_frequent();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}