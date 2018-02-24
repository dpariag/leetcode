// Leetcode: https://leetcode.com/problems/license-key-formatting/description/
// Given a string (S) of alphanumeric chars and dashes and an integer k:
// * Split S into blocks of size k, separated by dashes. The first block may contain < k chars.
// * Convert lower case chars to upper case

// Approach: Scan S from right to left, appending characters to result. Append dashes every k chars.
// O(n) time and space (not done in place)

#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 9ms. Beats 38.14% of submissions, ties 36.81% of submissions.
class Solution {
public:
    std::string licenseKeyFormatting(const std::string& s, int k) {
        std::string result;
        result.reserve(s.size());
        int i = s.size() - 1;
        while (i >= 0) {
            int j = 0;
            while (j < k && i >= 0) {
                if (std::isalnum(s[i])) { result.append(1, std::toupper(s[i])); ++j; }
                --i;
            }
            if (i >= 0) {result.append(1, '-'); }
        }
        while (!result.empty() && result.back() == '-') { result.pop_back(); }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

void test_license_key_formatting() {
    Solution soln;
    
    assert(soln.licenseKeyFormatting("--a-a-a-a--", 2) == "AA-AA");
    assert(soln.licenseKeyFormatting("2-4A0r7-4k", 3) == "24-A0R-74K");
    assert(soln.licenseKeyFormatting("2-4A0r7-4k", 4) == "24A0-R74K");
    assert(soln.licenseKeyFormatting("aBc-D", 1) == "A-B-C-D");
    assert(soln.licenseKeyFormatting("ABC-D", 2) == "AB-CD");
    assert(soln.licenseKeyFormatting("aBc-D", 2) == "AB-CD");    
}

int main(int argc, char** argv) {
    test_license_key_formatting();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
