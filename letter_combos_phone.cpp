// Leetcode: https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
// Given a digit string, return all possible letter combinations that the number could represent.

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

// Accepted. Beats 54.28% of submissions, ties 45.72% of submissions.
class Solution {
public:
    void combos(std::string& digits, int index, 
                std::string& cur, Strings& result) {
        if (index == digits.size()) {
            result.emplace_back(cur);
            return;
        }
        
        int digit = digits[index] - '0';
        const auto& chars = map[digit];

        for (auto ch : chars) {
            cur.append(1, ch);
            combos(digits, index+1, cur, result);
            cur.pop_back();
        }
    }

    Strings letterCombinations(std::string& digits) {
        Strings result;
        if (digits.empty()) { return result; }
        std::string cur;
        combos(digits, 0, cur, result);
        return result;
    }

private:
    std::string map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
};

bool test_combos(std::string digits, Strings expected) {
    Solution soln;

    auto combos = soln.letterCombinations(digits);
    std::sort(expected.begin(), expected.end()); 
    std::sort(combos.begin(), combos.end());
    return combos == expected;
}

void test_combos() {
    assert(test_combos("9", {"w","x","y","z"}));
    assert(test_combos("23", {"ad","ae","af","bd","be","bf","cd","ce","cf"}));
}

int main(int argc, char** argv) {
    test_combos();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
