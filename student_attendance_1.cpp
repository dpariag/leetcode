// Leetcode: https://leetcode.com/problems/student-attendance-record-i/description/
// Given a string containing 'A', 'L' and 'P' characters determine if it contains
// more than one 'A' or more than 2 consecutive 'L's.

// Approach: Scan the string counting 'A's and consecutive 'L's. O(n) time.

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 5ms. Beats 23.41% of submissions, ties < 1% of submisssions.
class Solution {
public:
    bool checkRecord(const std::string& s) {
        int num_As = 0, num_consecutive_Ls = 0;
        for (auto ch: s) {
            if (ch == 'A') {
                ++num_As;
                num_consecutive_Ls = 0;
            } else if (ch == 'L') {
                ++num_consecutive_Ls;
            } else if (ch == 'P') {
                num_consecutive_Ls = 0;
            }
            if (num_As > 1 || num_consecutive_Ls > 2) { return false; }
        }
        return true;
    }
};

void test_check_record() {
    Solution soln;

    assert(soln.checkRecord("") == true);
    assert(soln.checkRecord("A") == true);
    assert(soln.checkRecord("ALL") == true);
    assert(soln.checkRecord("AA") == false);
    assert(soln.checkRecord("ALLL") == false);
    assert(soln.checkRecord("APPLPPLPPLAPPP") == false);
    assert(soln.checkRecord("APPLPPLLLPPLPPP") == false);
    assert(soln.checkRecord("APPLPPLPPLLL") == false);
}

int main(int argc, char** argv) {
    test_check_record();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
