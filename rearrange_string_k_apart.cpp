// Leetcode: https://leetcode.com/problems/rearrange-string-k-distance-apart/description/
// Given a non-empty, lowercase string s and an integer k, rearrange s so that the same character 
// are at least k from each other. Return "" if no rearrangement is possible.

// Approach: For each character, track the # of occurrences of the character, and
// the next index at which it can be reused. Build the string one char at a time
// by appending the most common character that can be appended to s[i]. O(n) time.

#include <string>
#include <iostream>
#include <assert.h>

struct CharData {
    int counts[26] = {0};
    int index[26] = {0};
};

// Accepted. 17ms. Beats 76.53% of submissions, ties < 1% of submissions.
class Solution {
public:
    // Return the most common char which can be used at index
    inline char next_char(CharData& char_data, int index) {
        int next = -1, count = 0;
        for (int i = 0; i < 26; ++i) {
            if (char_data.index[i] <= index && char_data.counts[i] > count) {
                count = char_data.counts[i];
                next = i;
            }
        }
        return (next == -1) ? '\0' : 'a' + next;
    }

    std::string rearrangeString(const std::string& s, int k) {
        CharData char_data;
        for (auto ch : s) { char_data.counts[ch-'a']++; }
        
        int i = 0;
        std::string result;
        result.reserve(s.size());
        while (i < s.size()) {
            auto next = next_char(char_data, i);
            if (next == '\0') { return std::string(); }
            result.append(1, next);
            char_data.counts[next-'a']--;
            char_data.index[next-'a'] = i + k;
            ++i;
        }
        return result;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
