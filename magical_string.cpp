// Leetcode: https://leetcode.com/problems/magical-string/description/

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// 1 22 11 2 1 22 1 22 11 2 11 22
// 1 22 11 2 1 22 1 22 11 2 11 22

// Accepted. 6ms. Beats 55.06% of submissions, ties < 1% of submissions.
class Solution {
public:
    int magicalString(int n) {
        std::string magical("122");
        magical.reserve(100000);

        int i = 2;
        while (magical.size() < n) {
            char other = (magical.back() == '1') ? '2' : '1';
            int count = magical[i] - '0';
            magical.append(count, other);
            ++i;
        }

        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (magical[j] == '1') ++count;
        }
        return count;
    }
};

void test_magical() {
    Solution soln;

    assert(soln.magicalString(1) == 1);
    assert(soln.magicalString(2) == 1);
    assert(soln.magicalString(3) == 1);
    assert(soln.magicalString(4) == 2);
    assert(soln.magicalString(5) == 3);
    assert(soln.magicalString(19) == 9);    
}

int main(int argc, char** argv) {
    test_magical();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
