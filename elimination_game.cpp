// Leetcode: https://leetcode.com/problems/elimination-game/description/
// Using sorted integers from 1 to n, remove the first number and every other number until the end 
// Repeat the previous step, but from right to left, removing the last number then every other number
// Repeat from alternating ends, until a single number remains. Return that number

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// 9:28am
// Code and tests done at 9:44
// Leetcode found a bug, have to go to work
// Accepted. 62ms. Beats 50.26% of submissions, ties 6.25% of submissions.
class Solution {
public:
    int lastRemaining(int n) {
        if (n == 1) { return 1; }
        int first = 1, last = n, step_size = 2;
        bool left_side = true;

        // Remove odd numbers
        first = 2;
        last = (last % 2) ? last - 1 : last;
        step_size = 4, left_side = false;
        int length = n / 2;

        while (length > 1) {
            if (left_side) {
                first += (step_size / 2); 
                if (length % 2) { last -= (step_size / 2); }
            } else {
                last -= (step_size / 2);
                if (length % 2) { first += (step_size / 2); }
            }
            left_side = !left_side;
            step_size = step_size * 2;
            length -= (length % 2 ? (length / 2) + 1 : (length / 2));
        }
        return first;
    }
};

void test_elimination_game() {
    Solution soln;
    assert(soln.lastRemaining(1) == 1);
    assert(soln.lastRemaining(2) == 2);
    assert(soln.lastRemaining(3) == 2);
    assert(soln.lastRemaining(4) == 2);
    assert(soln.lastRemaining(5) == 2);
    assert(soln.lastRemaining(6) == 4);
    assert(soln.lastRemaining(7) == 4);
    assert(soln.lastRemaining(8) == 6);
    assert(soln.lastRemaining(16) == 6);
    assert(soln.lastRemaining(18) == 8);
}

int main(int argc, char** argv) {
    test_elimination_game();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
