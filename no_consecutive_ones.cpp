// Leetcode:https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/#/description
// Given a positive integer n, find the number of non-negative integers <= n, 
// whose binary representations do NOT contain consecutive ones.

// Brute Force:
// Better:

#include <deque>
#include <iostream>
#include <assert.h>

struct Pair {
    int64_t value = 0;  // a value with no consecutive ones in its bits
    int32_t index = 0;  // index of the next bit we manipulate
    Pair(int v, int i) : value(v), index(i) {}
}; 

class Solution {
public:
    int findIntegers(int num) {
        std::deque<Pair> values;
        int count = 1;
        values.emplace_back(Pair(0,0));

        while (!values.empty()) {
            auto& front = values.front();
            std::cout << "front (value, index) = " << front.value << "," << front.index << std::endl;
            std::cout << (front.value | (1 << front.index)) << std::endl;
            int64_t next = front.value | (1 << (front.index+1));
            if (front.index < 31 && next <= num) {
                values.emplace_back(Pair(front.value, front.index+1));
            }
            next = (front.value | (1 << front.index)) | (1 << (front.index + 2));
            if (front.index < 30 && next <= num) {
                values.emplace_back(Pair(front.value | (1 << front.index), front.index + 2));
            }
            values.pop_front();
            ++count;
        }
        //std::cout << "count = " << count << std::endl;
        return count;
    }
};

void test_find_integers() {
    Solution soln;

    assert(soln.findIntegers(1000000000) == 13);
    return;
    assert(soln.findIntegers(1) == 2);
    assert(soln.findIntegers(2) == 3);
    assert(soln.findIntegers(3) == 3);
    assert(soln.findIntegers(15) == 8);
    assert(soln.findIntegers(16) == 9);
    assert(soln.findIntegers(17) == 10);
    assert(soln.findIntegers(18) == 11);
    assert(soln.findIntegers(20) == 12);
    assert(soln.findIntegers(21) == 13);
}

int main(int argc, char** argv) {
    test_find_integers();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
