// Leetcode: https://leetcode.com/problems/cracking-the-safe/description/

// Approach: Starting with all zeros, re-use the last n-1 chars of the combination
// and append a new last character. Recurse until all k^n combinations of the alphabet
// have been hit.

#include <cmath>
#include <string>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Visited = std::unordered_set<std::string>;

// Accepted. 10ms. No runtime distribution chart available.
class Solution {
public:

    bool dfs_combo(int n, int k, int kn, std::string& combo, Visited& visited) {
        auto last_passwd = combo.substr(combo.size() - n, n);
        visited.emplace(last_passwd);
        if (visited.size() == kn) { return true; } // all combos tried

        std::string suffix = last_passwd.substr(1, n-1);
        for (int i = 0; i < k; ++i) {
            suffix.append(1, '0'+i);
            if (visited.count(suffix) == 0) {
                combo.append(1, '0'+i);
                if (dfs_combo(n, k, kn, combo, visited)) { return true; }
                combo.pop_back();
            }
            suffix.pop_back();
        }
        visited.erase(last_passwd);
        return false;
    }

    std::string crackSafe(int n, int k) {
        Visited visited;
        std::string combo(n, '0');
        int kn = std::pow(k, n);
        if (dfs_combo(n, k, kn, combo, visited)) { 
            //std::cout << combo << std::endl;
            return combo; 
        }
        return std::string();
    }
};

void test_crack_safe() {
    Solution soln;

    assert(soln.crackSafe(1, 2) == "01");
    assert(soln.crackSafe(2, 2) == "00110");
}

int main(int argc, char** argv) {
    test_crack_safe();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
