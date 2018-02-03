// Leetcode: https://leetcode.com/problems/1-bit-and-2-bit-characters/description/
// We have two special characters. The first character is represented by a '0' bit. 
// The second character is represented by two bits ('10' or '11'). Given a string,
// determine if it ends in the first character ('0').

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 9.24% of submissions, ties 53.60% of submissions.
class Solution {
public:
    bool isOneBitCharacter(const std::vector<int>& bits) {
        int i = 0, sz = bits.size();
        while (i < (sz - 1)) {
            bits[i] == 1 ? (i += 2) : (i +=1);
        }        
        return (i == (sz-1));
    }
};

void test_one_bit_char() {
    Solution soln;

    assert(soln.isOneBitCharacter({0}) == true);
    assert(soln.isOneBitCharacter({1,0}) == false);
    assert(soln.isOneBitCharacter({1,1}) == false);
    assert(soln.isOneBitCharacter({1,0,0}) == true);
    assert(soln.isOneBitCharacter({1,1,0}) == true);
    assert(soln.isOneBitCharacter({1,0,1,0}) == false);
    assert(soln.isOneBitCharacter({1,0,0,0}) == true);
    assert(soln.isOneBitCharacter({0,0,0}) == true);
}

int main(int argc, char** argv) {
    test_one_bit_char();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}