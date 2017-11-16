// Leetcode: https://leetcode.com/problems/lexicographical-numbers/#/description
// Given an integer n, return 1 - n in lexicographical order.
// For example, given 13, return: [1,10,11,12,13,2,3,4,5,6,7,8,9].

// Brute Force: Convert integers 1..n to strings, sort, and convert back to integers
// Better: Use arithmetic to ascend and descend when multiples of 10 are hit

#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using Numbers = std::vector<int>;

// Accepted. 125ms. Beats 99.18% of submissions.
class Solution {
public:
    Numbers lexicalOrder(int n) {
        Numbers result(n, 0);
        int next = 1;
        int generated = 0;
        while (generated < n) {
            result[generated++] = next;
            if (next == n) {
                next = next / 10;
                ++next;
                while (next % 10 == 0) { next = next / 10; }
            } else if (next * 10 <= n) {
                next *= 10;
            } else {
                ++next;
                while (next % 10 == 0) { next = next / 10; }
            }
        }
        return result;
    }
};

Numbers sort_lexically(int n) {
    std::vector<std::string> number_strings;
    for (auto i = 1; i <= n; ++i) {
        number_strings.emplace_back(std::to_string(i));
    } 
    std::sort(number_strings.begin(), number_strings.end());

    Numbers result;
    for (auto& ns : number_strings) {
        result.emplace_back(std::stoi(ns));
    }
    return result;
}

bool test_lexical_order(int n) {
    Solution soln;
    return (soln.lexicalOrder(n) == sort_lexically(n));
}

void test_lexical_order() {
    assert(test_lexical_order(1));
    assert(test_lexical_order(10));
    assert(test_lexical_order(20));
    assert(test_lexical_order(35));
    assert(test_lexical_order(111));
    assert(test_lexical_order(151));
    assert(test_lexical_order(192));
    assert(test_lexical_order(255));
    assert(test_lexical_order(10356));
}

int main(int argc, char** argv) {
    test_lexical_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
