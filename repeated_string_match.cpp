// Leetcode: https://leetcode.com/problems/repeated-string-match/description/

// Brute Force: Repeatedly append A to itself, search for B after each append. O(n*m)
// Better: Loop through A and B concurrently, wrapping the A index. O(n*m), but no string building. 

#include <string>
#include <cmath>
#include <iostream>
#include <assert.h>

// Accepted. 126ms. Beats 24.05% of submissions, ties < 1% of submissions.
class Solution {
public:
    int repeatedStringMatch(const std::string& A, const std::string& B) {
        const int a_size = int(A.size());
        const int b_size = int(B.size());
        int start = 0, repeats = 0;
        
        while (start < a_size) {
            if (A[start] == B.front()) {
                int a_index = start, b_index = 0;

                while (b_index < b_size) {
                    if (A[a_index] != B[b_index]) { break; }
                    ++b_index, ++a_index;
                    if (a_index == a_size && b_index < b_size) {
                        a_index = 0, ++repeats;
                    }
                }
                if (b_index == b_size) { return repeats + 1; }
            }
            ++start;
        }
        return -1;
    }
};

void test_repeated_string_match() {
    Solution soln;

    assert(soln.repeatedStringMatch("abababaaba", "aabaaba") == 2);
    assert(soln.repeatedStringMatch("abcd", "cdabcdab") == 3);
    assert(soln.repeatedStringMatch("xyz", "zxyzxyzxy") == 4);
    assert(soln.repeatedStringMatch("aa", "aaaaa") == 3);
    assert(soln.repeatedStringMatch("aa", "aaaaaa") == 3);
    assert(soln.repeatedStringMatch("aba", "abaabaa") == 3);
    assert(soln.repeatedStringMatch("ab", "ababa") == 3);
    assert(soln.repeatedStringMatch("ab", "ababab") == 3);
    assert(soln.repeatedStringMatch("ab", "abababa") == 4);
    assert(soln.repeatedStringMatch("ab", "xabababa") == -1);
    assert(soln.repeatedStringMatch("ab", "axbababa") == -1);
    assert(soln.repeatedStringMatch("ab", "abaxbaba") == -1);
    assert(soln.repeatedStringMatch("ab", "abababax") == -1);
}

int main(int argc, char** argv) {
    test_repeated_string_match();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}