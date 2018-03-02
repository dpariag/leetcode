// Leetcode: https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/
// Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

// Brute Force:
// Better: Can be reduced to the longest common substring problem. O(m*n) time and space

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 162ms. Beats 23.92% of submissions, ties 1.59% of submissions
class Solution {
public:
    int findLength(std::vector<int>& a, std::vector<int>& b) {
        std::vector<std::vector<int>> table(a.size()+1, std::vector<int>(b.size()+1, 0));
        int longest = 0;
        for (int i = 1; i < table.size(); ++i) {
            for (int j = 1; j < table[i].size(); ++j) {
                table[i][j] = (a[i-1] == b[j-1]) ? table[i-1][j-1] + 1 : 0;
                longest = std::max(longest, table[i][j]);
            }
        }
        return longest;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}