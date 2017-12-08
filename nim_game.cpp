// Leetcode: https://leetcode.com/problems/nim-game/description/
// There is a pile of stones on the table. Players take turns removing 1 to 3 stones. 
// The one who removes the last stone is the winner. Determine if the first player can win the game.

// Brute Force: Recursive enumeration of all game plays. O(3^n) time.
// Better: Dynamic programming can reduce runtime to O(n) by realizing the game is winnable
// with n stones if the name is not winnable with n-1, n-2, or n-3 stones. Count up from 1...n.
// This leads to the realization that the game is winnable if (n % 4) != 0

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 18.57% of submissions, ties 81.43% of submissions.
class Solution {
public:
    bool canWinNim(int n) {
        return (n % 4) != 0;
    }
};

void test_can_win() {
    Solution soln;

    assert(soln.canWinNim(1) == true);
    assert(soln.canWinNim(2) == true);
    assert(soln.canWinNim(3) == true);
    assert(soln.canWinNim(4) == false);
    assert(soln.canWinNim(5) == true);
    assert(soln.canWinNim(6) == true);
}

int main(int argc, char** argv) {
    test_can_win();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
