// Leetcode: https://leetcode.com/problems/sentence-screen-fitting/description/ 
// Given a rows x cols screen and a sentence (list of non-empty words), find how many times the 
// sentence can be fitted on the screen.

// Brute Force: Sweep the screen (rows x cols) placing words. O(m*n) time.
// Better: Compute a jump table. If row i begins with sentence[j], how many words fit on row i, 
// and what word does row i+1 begin with?
// Use the jump table to calculate the number of words that fit in each row

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 22ms. Beats 47.82% of submissions, ties 1.21% of submissions.
class Solution {
public:
    int wordsTyping(const std::vector<std::string>& sentence, int num_rows, int num_cols) {
        std::vector<int> table(sentence.size(), 0);
        int length = sentence.size();

        for (int i = 0; i < sentence.size(); ++i) {
            // If a row starts with sentence[i], what word does the next row start with?
            int room = num_cols, j = i;
            while (room > 0) {
                if (int(sentence[j % length].size()) <= room) {
                    room -= (sentence[j % length].size() + 1);
                } else { break; } // word does not fit
                ++j;
            }
            table[i] = j;
        }
        
        int num_words = 0, next_word = 0;
        for (int row = 0; row < num_rows; ++row) {
        	int index = next_word % length;
            num_words += table[index] - index;
            next_word =  table[index];
        }
        return num_words / length;
    }
};

void test_words_typing() {
    Solution soln;

    assert(soln.wordsTyping({"hello", "world"}, 2, 8) == 1);
    assert(soln.wordsTyping({"a", "bcd", "e"}, 3, 6) == 2);
    assert(soln.wordsTyping({"I", "had", "apple", "pie"}, 4, 5) == 1);
    assert(soln.wordsTyping({"I", "am", "a", "kitten"}, 10, 10) == 5);
}

int main(int argc, char** argv) {
    test_words_typing();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
