// Leetcode: https://leetcode.com/problems/utf-8-validation/description/ 
// Given an array of integers in which only the 8 least significant bits represent data, 
// determine whether it is a valid utf-8 encoding.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Useful byte masks
static const int byte_mask = 0xFF;
static const int top1 = 0x80;
static const int top2 = 0xC0;
static const int top3 = 0xE0;
static const int top4 = 0xF0;
static const int top5 = 0xF8;

// Accepted. 14ms. Beats 52.28% of submissions, ties 3.55% of submissions.
class Solution {
public:
    inline bool valid_bytes(const std::vector<int>& data, int i, int count) {
        if (data.size() - i < count) { return false; }
        for (int j = i+1; j < i+count; ++j) {
            int next_byte = data[j] & byte_mask;
            if ((next_byte & top2) != 0x80) { return false; }
        }
        return true;
    }

    bool validUtf8(const std::vector<int>& data) {
        int i = 0;
        while(i < data.size()) {
            int byte = data[i] & byte_mask; // rightmost 8 bits

            if ((byte & top5) == 0xF0) {
                // 4-byte char
                if (!valid_bytes(data, i, 4)) { return false; }
                i += 4;
            } else if ((byte & top4) == 0xE0) {
                // 3-byte char
                if (!valid_bytes(data, i, 3)) { return false; }
                i += 3;
            } else if ((byte & top3) == 0xC0) {
                // 2-byte char
                if (!valid_bytes(data, i, 2)) { return false; }
                i += 2;
            } else if ((byte & top1) == 0x00) {
                ++i;
            } else {
                return false;
            }
        }
        return true;
    }
};

void test_valid_utf8() {
    Solution soln;

    assert(soln.validUtf8({240,162,138,147,145}) == false);
    assert(soln.validUtf8({197,130,1}) == true);
    assert(soln.validUtf8({235,140,4}) == false);

}

int main(int argc, char** argv) {
    test_valid_utf8();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
