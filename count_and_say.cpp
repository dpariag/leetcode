// Leetcode: https://leetcode.com/problems/count-and-say/description/
// Given an integer n, generate the nth term of the count-and-say sequence.

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 23.64% of submissions, ties 64.97% of submissions
class Solution {
public:
    std::string countAndSay(int n) {
        if (n <= 0) { return ""; }
        int i = 1;
        std::string cur = "1";
        while (i < n) {
            char ch = cur.front();
            int j = 1, count = 1;
            std::string next;
            next.reserve(cur.size()*2);

            while (j < cur.size()) {
                if (cur[j] == ch) { 
                    ++count; 
                } else {
                    next.append(std::to_string(count));
                    next.append(1, ch);
                    ch = cur[j];
                    count = 1;
                }
                ++j;
            }
            next.append(std::to_string(count));
            next.append(1, ch);
            ++i;
            cur = next;
        }
        return cur;
    }
};

void test_count_and_say() {
    Solution soln;

    assert(soln.countAndSay(1) == "1");
    assert(soln.countAndSay(2) == "11");
    assert(soln.countAndSay(3) == "21");
    assert(soln.countAndSay(4) == "1211");
    assert(soln.countAndSay(5) == "111221");
    assert(soln.countAndSay(6) == "312211");
    assert(soln.countAndSay(7) == "13112221");
}

int main(int argc, char** argv) {
    test_count_and_say();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
