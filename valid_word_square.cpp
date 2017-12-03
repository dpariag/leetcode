// Leetcode: https://leetcode.com/problems/valid-word-square/description/
// Check whether a sequence of words forms a valid word square.
// A valid word square is one where the kth row and column contain identical strings.

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 13ms. Beats 86.52% of submissions, ties 9.13% of submissions.
class Solution {
public:
    bool validWordSquare(std::vector<std::string>& words) {
        int num_rows = words.size(); 

        for (int row = 0; row < words.size(); ++row) {
        	// Check if current row is too long
            if (words[row].size() > num_rows) { return false; }
            // Current row can't be longer than it's predecessor
            if (row >= 1 && words[row].size() > words[row-1].size()) { return false; }
            for (int col = 0; col < words[row].size(); ++col) {
            	// Check if transposed row is too short
                if (words[col].size() <= row) { return false; }
                // Check for a mismatch
                if (words[row][col] != words[col][row]) { return false; }
            }
        }
        return true;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
