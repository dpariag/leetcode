// Leetcode: https://leetcode.com/problems/longest-uncommon-subsequence-i/description/
//

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 72.23% of submissions, ties 27.77% of submissions.
class Solution {
public:
    int findLUSlength(string a, string b) {
        if (a.size() > b.size()) { return a.size(); }
        if (b.size() > a.size()) { return b.size(); }

        if (a == b) { return -1; }
        return a.size();
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
