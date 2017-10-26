// Leetcode: https://leetcode.com/problems/elimination-game/description/
// Using sorted integers from 1 to n, remove the first number and every other number until the end 
// Repeat the previous step, but from right to left, removing the last number then every other number
// Repeat from alternating ends, until a single number remains. Return that number

// Brute Force: Construct an array and iteratively remove alternating elements as described. 
// O(logn*n^2) time and O(n) space.
// Better: No need to construct an array. Instead, compute the values of the leftmost and rightmost
// elements in the sequence at each iteration. O(logN) time and O(1) space.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 62ms. Beats 50.26% of submissions, ties 6.25% of submissions.
class Solution {
public:
    int lastRemaining(int n) {
        if (n == 1) { return 1; }
        // Remove odd numbers, so the sequence looks like 2,4,6,...,last
        int first = 2, last = (n % 2) ? n-1 : n;
        int step_size = 2, length = n / 2;
        bool left_side = false;

        while (length > 1) {
            if (left_side) {
                // Advance left endpoint. Also advance right for odd-length sequences
                first += step_size; 
                if (length % 2) { last -= step_size; }
            } else {
                // Advance right endpoint. Also advance left for odd-length sequences
                last -= step_size;
                if (length % 2) { first += step_size; }
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
