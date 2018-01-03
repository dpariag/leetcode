// Leetcode: https://leetcode.com/problems/judge-route-circle/description/
// Initially, there is a Robot at position (0, 0). Given a string representing a sequence of moves 
// ('U' for up, 'D' for down, 'R' for right, 'L' for left) determine if the robot ends up in

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 19ms. Beats 33.73% of submissions, ties 55.38% of submissions.
class Solution {
public:
    bool judgeCircle(std::string moves) {
        int x = 0, y = 0;
        for (auto m : moves) {
            switch (m) {
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
                case 'L':
                    --x;
                    break;
                case 'R':
                    ++x;
                    break;
            }
        }
        return x == 0 && y == 0;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
