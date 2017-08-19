// Leetcode: https://leetcode.com/problems/maximum-product-of-word-lengths/description/ 
// Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where 
// the two words do not share common letters. You may assume that each word will contain only lower 
// case letters. If no such two words exist, return 0.

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 269ms. Beats 16.26% of submissions.
class Solution {
public:
    inline int calculate_product(const std::string& first, const std::string& second) {
        int first_bits = 0, second_bits = 0; 
        for (auto ch : first) {
            first_bits |= (1 << (ch -'a'));
        }
        
        for (auto ch : second) {
            second_bits |= (1 << (ch - 'a'));
        }

        if ((first_bits & second_bits) == 0) {
            return first.length() * second.length();
        }
        return 0;
    } 

    int maxProduct(std::vector<std::string>& words) {
        int max_product = 0;
        for (int i = 0; i < words.size(); ++i) {
            std::sort(words[i].begin(), words[i].end());
        }
        std::sort(words.begin(), words.end());
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i+1; j < words.size(); ++j) {
                if (words[i][0] != words[j][0]) {
                    auto product = calculate_product(words[i], words[j]);
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
