// Leetcode: https://leetcode.com/problems/find-the-celebrity/description/

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

bool knows(int a, int b);

// Accepted. 62ms. Beats 38.01% of submissions, ties < 5.53% of submissions.
class Solution {
public:
    bool knows_no_one(int cur, int n) {
        for (int i = 0; i < n; ++i) {
            if (i != cur && knows(cur, i)) { return false; }
        }
        return true;
    }

    int findCelebrity(int n) {
        // First scan for someone who knows no-one
        for (int i = 0; i < n; ++i) {
            if (knows_no_one(i, n)) {
                // Possible celebrity
                bool celebrity = true;
                for (int j = 0; j < n; ++j) {
                    if (j != i && knows(j, i) == false) {
                        celebrity = false;
                        break;
                    }
                }
                if (celebrity) {
                    // i knows nobody, and everyone knows i 
                    return i; 
                }
            }
        }
        return -1;
    }
};


int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}