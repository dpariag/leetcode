// Leetcode: https://leetcode.com/problems/string-compression/description/

// Approach: Scan the string counting blocks of the same character. 
// Replace each block with an abbreviation of the form char[count]. O(n) time, O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 27.21% of submissions, ties 72.73% of submissions.
class Solution {
public:
    void append(std::vector<char>& chars, int& write, int count, int ch) {
        chars[write++] = ch;
        if (count > 1) {
            std::string num;
            while (count > 0) {
                num.push_back('0' + (count % 10));
                count = count / 10;
            }

            for (int i = int(num.size())-1; i >= 0; --i) {
                chars[write++] = num[i];
            }
        }
    }

    int compress(std::vector<char>& chars) {
        int read = 1, write = 0, count = 1;
        char ch = chars[0];
        while (read < chars.size()) {
            if (chars[read] != ch) {
                append(chars, write, count, ch);
                ch = chars[read];
                count = 0;
            }
            ++count;
            ++read;
        }
        append(chars, write, count, ch);
        return write;
    }
};

bool test_string_compression(std::vector<char> chars, std::vector<char> expected) {
    Solution soln;
    int len = soln.compress(chars);
    for (int i = 0; i < expected.size(); ++i) {
        if (chars[i] != expected[i]) { return false; }        
    }
    return len == expected.size();
}

void test_string_compression() {
    assert(test_string_compression({'a'}, {'a'}));
    assert(test_string_compression({'a','a'}, {'a','2'}));
    assert(test_string_compression({'a','a','b'}, {'a','2','b'}));
    assert(test_string_compression({'a','a','b','a'}, {'a','2','b','a'}));
    assert(test_string_compression({'a','a','b','a','a','a'}, {'a','2','b','a','3'}));
    assert(test_string_compression({'a','a','b','a','a','a','a','a','a','a','a','a','a','a','a'}, 
                                   {'a','2','b','a','1','2'}));
    assert(test_string_compression({'a','a','b','b','c','c','c'}, {'a','2','b','2','c','3'}));
}

int main(int argc, char** argv) {
    test_string_compression();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}