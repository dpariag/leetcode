// Leetcode:https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/#/description
// Given a positive integer n, find the number of non-negative integers <= n, 
// whose binary representations do NOT contain consecutive ones.

// Brute Force:
// Better:

#include <iostream>
#include <assert.h>

const int num_block_values = 8;
int block_values[num_block_values] = {0,1,2,4,5,8,9,10};

struct BlockCount {
    int num_00 = 0; // 0..0 (i.e, starts and ends with a zero bit)
    int num_01 = 0; // 0..1
    int num_10 = 0; // 1..0
    int num_11 = 0; // 1..1

    BlockCount() : num_00(0), num_01(0), num_10(0), num_11(0) {}
    BlockCount(int n00, int n01, int n10, int n11): 
        num_00(n00), num_01(n01), num_10(n10), num_11(n11) {}

    BlockCount& operator+=(const BlockCount& other) {
        num_00 += other.num_00;
        num_01 += other.num_01;
        num_10 += other.num_10;
        num_11 += other.num_11;
        return *this;
    }
    int count() const { return num_00 + num_01 + num_10 + num_11; }
};

BlockCount mult(const BlockCount& a, const BlockCount& b) {
    BlockCount rhs;
    rhs.num_00 = a.num_00 * (b.num_00 + b.num_10) + a.num_01 * (b.num_00);
    rhs.num_01 = a.num_01 * (b.num_01) + a.num_00 * (b.num_01 + b.num_11);
    rhs.num_10 = a.num_10 * (b.num_00 + b.num_10) + a.num_11 * (b.num_00);
    rhs.num_11 = a.num_10 * (b.num_01 + b.num_11) + a.num_11 * (b.num_01);
    return rhs;
}

// Accepted. Beats 98.88% of submissions, ties 1.12% of submissions.
class Solution {
public:
    inline void find_block(BlockCount& count, int b) {
        if ((b & 9) == 0) {
            ++count.num_00;
        } else if ((b & 9) == 8) {
            ++count.num_10;
        } else if ((b & 9) == 1) {
            ++count.num_01;
        } else if ((b & 9) == 9) {
            ++count.num_11;
        }
    }

    inline BlockCount count_integers(int up_to) {
        BlockCount result;
        for (int i = 0; i < num_block_values; ++i) {
            if (block_values[i] <= up_to) {
                find_block(result, block_values[i]);
            }
        }
        return result;
    }

    inline BlockCount count_block(int block, BlockCount& full_block, BlockCount& rollover) {
        BlockCount result;
        for (int i = 0; i < num_block_values; ++i) {
            BlockCount b;
            find_block(b, block_values[i]);
            if (block_values[i] < block) {
                result += mult(b, full_block);
            } else if (block_values[i] == block) {
                result += mult(b, rollover);
            } else { break; }
        }
        return result;
    }

    int findIntegers(int num) {
        int mask = 15;
        int cur_block = num & mask;
        BlockCount full_block = count_integers(mask);
        BlockCount full_block4 = full_block;
        BlockCount rollover = count_integers(cur_block);
        if (num <= mask) { return rollover.count(); }

        num = num >> 4;
        int num_blocks = 0;
        BlockCount result;
        while (num != 0) {
            ++num_blocks;
            cur_block = num & mask;
            result = count_block(cur_block, full_block, rollover);
            num = num >> 4;
            if (num != 0) {
                full_block = mult(full_block, full_block4);
                rollover = result;
            }
        }
        return result.count();
    }
};


void test_find_integers() {
    Solution soln;
    assert(soln.findIntegers(1) == 2);
    assert(soln.findIntegers(2) == 3);
    assert(soln.findIntegers(3) == 3);
    assert(soln.findIntegers(15) == 8);
    assert(soln.findIntegers(16) == 9);
    assert(soln.findIntegers(17) == 10);
    assert(soln.findIntegers(18) == 11);
    assert(soln.findIntegers(20) == 12);
    assert(soln.findIntegers(21) == 13);
    assert(soln.findIntegers(64) == 22);
    assert(soln.findIntegers(65) == 23);
    assert(soln.findIntegers(146) == 45);
    assert(soln.findIntegers(276) == 67);
    assert(soln.findIntegers(325) == 81);
    assert(soln.findIntegers(168992) == 6313);
    assert(soln.findIntegers(327840) == 9397);
    assert(soln.findIntegers(349474) == 10928);
    assert(soln.findIntegers(33636370) ==200000);
    assert(soln.findIntegers(89478472) == 514222);
}

int main(int argc, char** argv) {
    test_find_integers();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
