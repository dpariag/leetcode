// Leetcode: https://leetcode.com/problems/combinations/description/
// Given two integers n and k, return all possible combinations of k chosen from 1..n.

// Approach: Use recursion driven by the binomial coefficient formula:
// choose(n,k) = choose(n-1, k-1) + choose(n-1, k)

#include <vector>
#include <iostream>
#include <assert.h>

using Combo = std::vector<int>;
using Combos = std::vector<Combo>;

// Accepted. 86ms. Beats 36.34% of submissions, ties 5.79% of submissions.
class Solution {
public:
    void build_combos(Combos& result, Combo& cur, int n, int k, int i) {
        if (k == 0) {
            result.emplace_back(cur);
            return;
        }
    
        if (i <= n) {
            // Choose i 
            cur.emplace_back(i);
            build_combos(result, cur, n, k-1, i+1);

            // Don't choose i
            cur.pop_back();
            build_combos(result, cur, n, k, i+1);
        }
    }

    Combos combine(int n, int k) {
        Combos result;
        Combo cur;
        build_combos(result, cur, n, k, 1);
        return result; 
    }
};

bool test_combine(int n, int k, Combos expected) {
    Solution soln;
    auto combos = soln.combine(n, k);
    return combos == expected;
}

void test_combine() {
    assert(test_combine(1, 1, {{1}}));
    assert(test_combine(2, 1, {{1}, {2}}));
    assert(test_combine(2, 2, {{1,2}}));
    assert(test_combine(3, 2, {{1,2},{1,3},{2,3}}));
    assert(test_combine(4, 2, {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}}));
}

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
