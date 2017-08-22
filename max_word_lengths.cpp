// Leetcode: https://leetcode.com/problems/maximum-product-of-word-lengths/description/ 
// Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where 
// the two words do not share common letters. You may assume that each word will contain only lower 
// case letters. If no such two words exist, return 0.

// Brute Force: Compare all pairs of words, looking for words with no common letters. O(m*n^2)
// Better: Represent the letters in a word by a 32-bit mask, making it easy to identify letter sets
// with a null intersection. O(n^2 + m)

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 39ms. Beats 96.96% of submissions, ties 3.04% of submissions
class Solution {
public:
    inline int build_bitmask(const std::string& str) {
        int mask = 0;
        for (auto ch : str) {
            mask |= (1 << (ch -'a'));
        }
        return mask;
    } 

    int maxProduct(std::vector<std::string>& words) {
        std::vector<int> masks(words.size(), 0);
        for (int i = 0; i < words.size(); ++i) {
            masks[i] = build_bitmask(words[i]);
        }

        int max_product = 0;
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i+1; j < words.size(); ++j) {
                if ((masks[i] & masks[j]) == 0) {
                    int product = words[i].length() * words[j].length();
                    max_product = std::max(max_product, product);
                }
            }
        }
        return max_product;
    }
};

bool test_max_product(std::vector<std::string> words, int expected_product) {
    Solution soln;
    auto product = soln.maxProduct(words);
    return product == expected_product;
}

void test_max_product() {
    assert(test_max_product({"abcd","abcd"}, 0));
    assert(test_max_product({"abcd","efgh"}, 16));
    assert(test_max_product({"ab","bf","af","fb"}, 0));
    assert(test_max_product({"ab","bf","af","zyz"}, 6));
    assert(test_max_product({"aaaaa","bf","af","zyz"}, 15));
}

int main(int argc, char** argv) {
    test_max_product();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
