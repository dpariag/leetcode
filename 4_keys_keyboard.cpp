// Leetcode: https://leetcode.com/problems/4-keys-keyboard/description/
// Given a keyboard with 4 keys: {"A", "Select", "Copy", "Paste"}, determine
// the largest number of "A"s that can be obtained with N keystrokes.

// Brute Force: Generate all permutations of N keystrokes, track max "A"s generated. O(N!) time.
// Better: DP based approach. Max A's over N keystrokes can be calculated from 
// max A's over 1...N-3 keystrokes. O(N^2) time

#include <vector>
#include <iostream>
#include <assert.h>

class Solution {
public:
    int maxA(int n) {
        std::vector<int64_t> counts(n+1, 0);

        for (int i = 0; i < counts.size(); ++i) {
            if (i <= 6) {
                counts[i] = i;
            } else {
                int64_t max = i; // can always get i 'A's
                for (int j = i-3; j >= 1; --j) {
                    int64_t num_pastes = (i - j - 2);
                    max = std::max(max, counts[j]*(num_pastes+1));
                }
                counts[i] = max;
            }
        }
        return counts[n];
    }
};

void test_max_A() {
    Solution soln;

    assert(soln.maxA(0) == 0);
    assert(soln.maxA(1) == 1);
    assert(soln.maxA(2) == 2);
    assert(soln.maxA(3) == 3);
    assert(soln.maxA(4) == 4);
    assert(soln.maxA(5) == 5);
    assert(soln.maxA(6) == 6);
    assert(soln.maxA(7) == 9);
    assert(soln.maxA(8) == 12);
}

int main(int argc, char** argv) {
    test_max_A();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}