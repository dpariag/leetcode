// Leetcode: https://leetcode.com/problems/restore-ip-addresses/description/
// Given a string containing only digits, restore it by returning all possible valid IP address combinations.

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 10.01% of submissions, ties 71.31% of submissions.
class Solution {
public:
    std::vector<std::string> restoreIpAddresses(const std::string& s) {
        int block1 = 0, block2 = 0, block3 = 0, block4 = 0;
        std::vector<std::string> result;

        for (int i = 0; i < 3; ++i) {
            if (i > 0 && block1 == 0) { break; } // Don't allow leading zeroes
            block1 = (block1*10) + s[i]-'0';
            block2 = 0;
            for (int j = i + 1; block1 <= 255 && j < i + 4; ++j) {
                if (j-i > 1 && block2 == 0) { break; }
                block2 = (block2*10) + s[j]-'0';
                block3 = 0;
                for (int k = j + 1; block2 <= 255 && k < j + 4; ++k) {
                    if (k-j > 1 && block3 == 0) { break; }
                    block3 = (block3*10) + s[k]-'0';
                    if (block3 <= 255 && ((int(s.size()) - k - 1) <= 3)) {
                        block4 = 0;
                        int appended = 0;
                        for (int l = k +1; l < s.size(); ++l) {
                            if (l-k > 1 && block4 == 0) {
                                block4 = 256;
                                break;
                            }
                            block4 = (block4*10) + s[l]-'0';
                            ++appended;
                        }
                        if (appended && block4 <= 255) {
                            std::string ip = s.substr(0, i+1);
                            ip.append(1,'.');
                            ip.append(s.substr(i+1, j-i));
                            ip.append(1, '.');
                            ip.append(s.substr(j+1, k-j));
                            ip.append(1, '.');
                            ip.append(s.substr(k+1, s.size()));
                            result.emplace_back(ip);
                        }
                    }
                }
            }
        }
        return result;
    }
};


bool test_ip_addresses(std::string digits, std::vector<std::string> expected) {
    Solution soln;

    auto ips = soln.restoreIpAddresses(digits);
    std::sort(ips.begin(), ips.end());
    std::sort(expected.begin(), expected.end());
    return ips == expected;
}

void test_ip_addresses() {
    assert(test_ip_addresses("010010", {"0.10.0.10","0.100.1.0"}));
    assert(test_ip_addresses("1111", {"1.1.1.1"}));
    assert(test_ip_addresses("25525511135", {"255.255.11.135", "255.255.111.35"}));
}

int main(int argc, char** argv) {
    test_ip_addresses();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
