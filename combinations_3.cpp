// Leetcode: 
// Find all possible combinations of k numbers that add up to a number n, given that only numbers from 
// 1 to 9 can be used and each combination should be a unique set of numbers.

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Combo = std::vector<int>;
using Combos = std::vector<Combo>;

// Accepted. 0ms. Beats 32.34% of submissions, ties 67.66% of submissions.
class Solution {
public:
    void build_combos(int k, int n, int cur, Combos& combos, Combo& combo) {
        if (combo.size() == k && n == 0) {
            combos.emplace_back(combo);
            return;
        } 

        for (int num = cur; num <= 9; ++num) {
            if (n-num >= 0) {
                combo.emplace_back(num);
                build_combos(k, n-num, num+1, combos, combo);
                combo.pop_back();
            }
        }
    }


    Combos combinationSum3(int k, int n) {
        Combos combos;
        Combo c;
        build_combos(k, n, 1, combos, c);
        return combos;    
    }
};

bool test_combos(int k, int n, Combos expected) {
    Solution soln;

    auto result = soln.combinationSum3(k, n);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    return result == expected;
}

void test_combos() {
    assert(test_combos(0,0, {{}}));
    assert(test_combos(1,1, {{1}}));
    assert(test_combos(1,5, {{5}}));
    assert(test_combos(2,5, {{1,4},{2,3}}));
    assert(test_combos(3,7, {{1,2,4}}));
    assert(test_combos(3,9, {{1,2,6}, {1,3,5}, {2,3,4}}));
}

int main(int argc, char** argv) {
    test_combos();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
