// Leetcode: https://leetcode.com/problems/excel-sheet-column-title/description/
// Given a positive integer, return its corresponding column title as appear in an Excel sheet.

// Approach: The rightmost column represents 26^0, the next 26^1, etc.
// However, there is no zero value allowed in a column.
// Iterate columns from right to left, greedily taking the largest value possible into each column.
// Subtract the value taken and move onto the next column. O(n) time and O(1) space.

#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 17.60% of submissions, ties 82.40% of submissions.
class Solution {
public:
    std::string convertToTitle(int n) {
        std::string result;
        int64_t cur_col = 1, next_col = 26;
        while (n > 0) {
            auto val = (n / next_col);
            auto rem = n - (val * next_col);
            if (rem == 0) {
                result.append(1, 'Z');
                n -= (26*cur_col);
            } else {
                result.append(1, 'A' + (rem/cur_col)-1);
                n -= rem;
            }
            cur_col = next_col;
            next_col = next_col*26;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

void test_convert_to_title() {
    Solution soln;

    assert(soln.convertToTitle(1) == "A");
    assert(soln.convertToTitle(2) == "B");
    assert(soln.convertToTitle(26) == "Z");
    assert(soln.convertToTitle(27) == "AA");
    assert(soln.convertToTitle(28) == "AB");
    assert(soln.convertToTitle(52) == "AZ");
    assert(soln.convertToTitle(677) == "ZA");
    assert(soln.convertToTitle(1381) == "BAC");
    assert(soln.convertToTitle(1000000001) == "CFDGSXM");
}

int main(int argc, char** argv) {
    test_convert_to_title();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
