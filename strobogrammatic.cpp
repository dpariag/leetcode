// Leetcode: https://leetcode.com/problems/strobogrammatic-number/description/
// A strobogrammatic number is a number that looks the same when rotated 180 degrees 
// (looked at upside down). Determine if a number, represented as a string, is strobogrammatic.

// Approach: Build the rotated number character by character. Non-symmetric numbers are replaced by 'x'
// O(n) time and space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 12.39% of submissions, ties 87.61% of submissions.
class Solution {
public:
    bool isStrobogrammatic(const std::string& num) {
        char map[10] = {'0','1','x','x','x','x','9','x','8','6'};
        std::string rotated;
        
        for (int i = num.size() - 1; i >= 0; --i) {
            rotated.append(1, map[num[i]-'0']);
        }
        return rotated == num;
    }
};

void test_strobogrammatic() {
    Solution soln;

    assert(soln.isStrobogrammatic("69") == true);
    assert(soln.isStrobogrammatic("6969") == true);
    assert(soln.isStrobogrammatic("212") == false);
    assert(soln.isStrobogrammatic("818") == true);
    assert(soln.isStrobogrammatic("88") == true);
    assert(soln.isStrobogrammatic("888") == true);
    assert(soln.isStrobogrammatic("808") == true);
    assert(soln.isStrobogrammatic("818") == true);
}

int main(int argc, char** argv) {
    test_strobogrammatic();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
