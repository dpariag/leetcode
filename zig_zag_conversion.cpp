// Leetcode: https://leetcode.com/problems/zigzag-conversion/description/
//

// Brute Force: Store n rows, and append each char to it's destination row. Concatenate rows at the end. O(n) time.
// Better: Build the final string by noting that the next char in each row can be computed. O(n) time.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 38ms. Beats 34.03% of submissions, ties 2.57% of submissions.
class Solution {
public:
    std::string convert(const std::string& s, int num_rows) {
        if (num_rows == 1 || s.size() < num_rows) { return s; }
        std::string result;
        result.reserve(s.size());

        num_rows = std::min(num_rows, int(s.size()));
        // from_top : num chars to go to the top and come back down to current row
        // from_bottom : num chars to go to the bottom and come back up to current row
        int from_top = 0, from_bottom = (num_rows-1)*2;
        for (int row = 0; row < num_rows; ++row) {
            int idx = row;
            result.push_back(s[row]);
            while (idx < s.size()) {
                if (from_bottom > 0) {
                    idx += from_bottom;
                    if (idx < s.size()) result.push_back(s[idx]);
                }
                if (from_top > 0) {
                    idx += from_top;
                    if (idx < s.size()) result.push_back(s[idx]);
                }
            }
            from_top += 2;
            from_bottom -= 2;
        }
        return result;
    }
};

void test_zig_zag() {
    Solution soln;

    assert(soln.convert("A", 2) == "A");
    assert(soln.convert("abc", 5) == "abc");
    assert(soln.convert("abc", 1) == "abc");
    assert(soln.convert("abc", 2) == "acb");
    assert(soln.convert("PAYPALISHIRING", 1) == "PAYPALISHIRING");
    assert(soln.convert("PAYPALISHIRING", 2) == "PYAIHRNAPLSIIG");
    assert(soln.convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    assert(soln.convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    assert(soln.convert("PAYPALISHIRING", 5) == "PHASIYIRPLIGAN");
    assert(soln.convert("PAYPALISHIRING", 14) == "PAYPALISHIRING");
}

int main(int argc, char** argv) {
    test_zig_zag();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
