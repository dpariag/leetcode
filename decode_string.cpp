// Leetcode: https://leetcode.com/problems/decode-string/description/    
// Decode a string that has been encoded using the format: k[encoded_string], where the 
// encoded_string inside the square brackets is repeated exactly k times. Note k > 0.

// Brute Force: Multiple passes over input, expanding all non-nested encoded strings on each pass.
// Better: Use recursion to expand nested encodings. Each encoding is generated once and never moves.

#include <vector>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <assert.h>

// Accepted. 0ms. Beats 50.95% of submissions, ties 49.05% of submissions.
class Solution {
public:
    std::string decode(const std::string& s, int& offset) {
        std::string result;
        int i = offset, repeat = 0;
        while (i < s.size()) {
            if (std::isdigit(s[i])) {
                repeat = (repeat*10) + s[i] - '0';
            } else if (s[i] == '[') {
                auto nested = decode(s, ++i);
                for (; repeat > 0; --repeat) { result.append(nested); }
            } else if (s[i] == ']') {
                break;
            } else {
                result.append(1, s[i]);
            }
            ++i;
        }
        offset = i;
        return result;
    }

    std::string decodeString(const std::string& s) {
        int offset = 0;
        return decode(s, offset);
    }
};

void test_decode() {
    Solution soln;
    assert(soln.decodeString("") == "");
    assert(soln.decodeString("a") == "a");
    assert(soln.decodeString("abcd") == "abcd");
    assert(soln.decodeString("ab15[c]d") == "abcccccccccccccccd");
    assert(soln.decodeString("ab2[xy]cd") == "abxyxycd");
    assert(soln.decodeString("ab2[x99[]y]cd") == "abxyxycd");
    assert(soln.decodeString("ab2[xy]3[zz]cd") == "abxyxyzzzzzzcd");
    assert(soln.decodeString("ab2[1[xy]]3[zz]cd") == "abxyxyzzzzzzcd");
    assert(soln.decodeString("5[r]ab2[1[xy]]3[zz]cd") == "rrrrrabxyxyzzzzzzcd");
    assert(soln.decodeString("ab2[1[xy]]3[zz]cd2[pt]") == "abxyxyzzzzzzcdptpt");
    assert(soln.decodeString("ab2[1[x2[O]y]]3[zz]cd2[pt]") == "abxOOyxOOyzzzzzzcdptpt");
    assert(soln.decodeString("ab2[1[x2[0[N]O]y]]3[zz]cd2[pt]EE") == "abxOOyxOOyzzzzzzcdptptEE");
}

int main(int argc, char** argv) {
    test_decode();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
