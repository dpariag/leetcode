// Leetcode: https://leetcode.com/problems/magical-string/description/

// Approach: Generate the magical string up to length N by discovering the
// pattern required to generate it. Count '1's in the first N chars. O(n) time/space.

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 8ms. Beats 55.06% of submissions, ties < 1% of submissions.
class Solution {
public:
    int magicalString(int n) {
        std::string magical("122");
        magical.reserve(n);

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