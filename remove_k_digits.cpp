// Leetcode: https://leetcode.com/problems/remove-k-digits/description/ 
// Given a non-negative integer represented as a string, remove k digits to obtain the smallest 
// possible number.

// Brute Force: Try all n choose k possibilities, and track the smallest.
// Better: Iterate the string using a stack to build the result. Append next digit if it is 
// >= stack.top(). Pop stack if next digit is < stack.top(). O(n) time and space.

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 66.41% of submissions, ties 33.59% of submissions.
class Solution {
public:
    std::string removeKdigits(std::string& num, int k) {
        std::string result;
        int i = 0, num_removed = 0;
        while (i < num.size()) {
            if (result.empty()) {
                if (num[i] != '0') { result.push_back(num[i]); }
            } else if (num[i] >= result.back()) {
                result.push_back(num[i]);
            } else if (num[i] < result.back()) {
                if (num_removed < k) {
                    result.pop_back();
                    ++num_removed;
                    continue;
                }
                result.push_back(num[i]);
            }
            ++i;
        }
        
        while (num_removed < k && !result.empty()) {
            result.pop_back();
            ++num_removed;
        }
        if (result.empty()) { result = "0"; }
        return result;
    }
};

bool test_remove_k_digits(std::string num, int k, std::string expected) {
    Solution soln;
    return soln.removeKdigits(num, k) == expected; 
}

void test_remove_k_digits() {
    assert(test_remove_k_digits("4567", 2, "45"));
    assert(test_remove_k_digits("7654", 2, "54"));
    assert(test_remove_k_digits("7645", 2, "45"));
    assert(test_remove_k_digits("765432", 2, "5432"));
    assert(test_remove_k_digits("765432", 3, "432"));
    assert(test_remove_k_digits("768974", 3, "674"));
    assert(test_remove_k_digits("1264892", 4, "122"));
    assert(test_remove_k_digits("991146", 3, "114"));
    assert(test_remove_k_digits("991146", 0, "991146"));
    assert(test_remove_k_digits("991146", 100, "0"));
    assert(test_remove_k_digits("10200", 1, "200"));
}

int main(int argc, char** argv) {
    test_remove_k_digits();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
