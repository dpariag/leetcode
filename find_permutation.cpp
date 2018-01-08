// Leetcode: https://leetcode.com/problems/find-permutation/description/

// Brute Force:
// Better:

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <assert.h>

// Accepted. 100ms. Beats 6.86% of submissions, ties < 1% of submissions.
class Solution {
public:
    std::vector<int> findPermutation(const std::string& s) {
        std::set<int> values;
        // Add all the values to the map
        for (int i = 1; i <= s.size()+1; ++i) { values.emplace(i); }

        std::vector<int> decreases(s.size()+1, 0);
        std::string s1 = "I" + s;
        int count = 0;
        for (int i = s1.size()-1; i >= 0; --i) {
            decreases[i] = count;
            if (s1[i] == 'I') { 
                count = 0; 
            } else {
                ++count;
            }
        }

        std::vector<int> perm(s.size()+1, 0);
        int digit = *values.lower_bound(*values.begin() + decreases[0]);
        values.erase(digit);
        perm[0] = digit;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == 'D') {
                perm[i+1] = perm[i] - 1;
            } else {
                int digit = *values.lower_bound(*values.begin() + decreases[i+1]);
                perm[i+1] = digit;
            }
            values.erase(perm[i+1]);
        }
        return perm;
    }
};

void test_find_permutation() {
    Solution soln;
    using Permutation = std::vector<int>;
        
    assert(soln.findPermutation("D") == Permutation({2,1}));
    assert(soln.findPermutation("I") == Permutation({1,2}));
    assert(soln.findPermutation("DI") == Permutation({2,1,3}));
    assert(soln.findPermutation("IDID") == Permutation({1,3,2,5,4}));
    assert(soln.findPermutation("DDID") == Permutation({3,2,1,5,4}));
    assert(soln.findPermutation("DDII") == Permutation({3,2,1,4,5}));
    assert(soln.findPermutation("IDID") == Permutation({1,3,2,5,4}));
    assert(soln.findPermutation("IIII") == Permutation({1,2,3,4,5}));
    assert(soln.findPermutation("DDDD") == Permutation({5,4,3,2,1}));
}

int main(int argc, char** argv) {
    test_find_permutation();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
