// Leetcode: https://leetcode.com/problems/word-squares/description/
// Given a set of words (without duplicates), find all word squares you can build from them.
// A sequence of words is a valid word square if the kth row and column are the same string, 
// where 0 ≤ k < max(numRows, numColumns).

// Brute Force: Build all possible squares, check if each is valid
// Better: Recursive enumeration. Build the square row by row, only expanding the board if
// a valid next word is available.

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using Square = std::vector<std::string>;
using Squares = std::vector<Square>;
using PrefixMap = std::unordered_map<std::string, Words>;

// Accepted. 55ms. Beats 68.63% of submissions, ties 0.33% of submissions.
class Solution {
public:
    inline void build_prefixes(PrefixMap& prefix_map, const std::string& word) {
        std::string prefix;        
        prefix_map[prefix].emplace_back(word);
        for (auto ch : word) {
            prefix.append(1, ch);
            prefix_map[prefix].emplace_back(word);
        }
    }

    void word_square(PrefixMap& prefix_map, Square& square, Squares& complete) {
        if (!square.empty() && square.size() == square[0].size()) {
            complete.emplace_back(square);
            return;
        }

        std::string prefix;
        for (int row = 0; row < int(square.size()); ++row) {
            prefix.append(1, square[row][square.size()]);
        }

        const auto& matching_words = prefix_map[prefix];
        for (const auto& word : matching_words) {
            square.emplace_back(word);
            word_square(prefix_map, square, complete);
            square.pop_back();
        }
    }

    Squares wordSquares(const Words& words) {
        PrefixMap prefix_map;

        for (const auto& w : words) {
            build_prefixes(prefix_map, w);
        }

        Squares complete;
        Square square;
        word_square(prefix_map, square, complete);
        return complete;
    }
};

bool test_word_squares(Words words, Squares expected) {
    Solution soln;

    auto squares = soln.wordSquares(words);
    std::sort(squares.begin(), squares.end());
    std::sort(expected.begin(), expected.end());
    return squares == expected;
}

void test_word_squares() {
    assert(test_word_squares({"area", "lead", "wall", "lady", "ball"}, 
           {{"wall", "area", "lead", "lady"}, 
            {"ball", "area", "lead", "lady"}}));
}

int main(int argc, char** argv) {
    test_word_squares();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
