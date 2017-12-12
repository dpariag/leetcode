// Leetcode: https://leetcode.com/problems/add-digits/description/
// Given a non-negative integer num, repeatedly add its digits until the sum is one digit.
// Example: num = 38 : 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.


// Brute Force: Loop over digits computing a sum, recurse on the sum until it is a single digit.
// Can be improved to a single pass by keeping the sum under 10 and extracting carrys
// Better: Note the pattern that numbers end up mapping to their value % 9. 
// Exceptions are zero, and numbers evenly divisible by 9.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 8.82% of submissions, ties 45.16% of submissions.
class IterativeSolution {
public:
    int addDigits(int num) {
        int carry = 0, sum = 0;
        while (num != 0) {
            auto digit = num % 10;
            num = num / 10;
            sum += digit;
            carry += (sum / 10);
            sum = sum % 10;
            if (num == 0) {
                num = carry;
                carry = 0;
            }
        }
        return sum;
    }
};

// Accepted. 3ms. Beats 53.99% of submissions, ties 46.01% of submissions.
class ConstantSolution {
    public:
    int addDigits(int num) {
        if (num == 0) { return 0; }
        auto rem = num % 9;
        if (rem == 0) { return 9; }
        return rem;
    }
};

template<typename Solution>
void test_add_digits() {
    Solution soln;

    assert(soln.addDigits(0) == 0);
    assert(soln.addDigits(1) == 1);
    assert(soln.addDigits(45) == 9);
    assert(soln.addDigits(99) == 9);
    assert(soln.addDigits(555) == 6);
    assert(soln.addDigits(668) == 2);
    assert(soln.addDigits(55588) == 4);
}

int main(int argc, char** argv) {
    test_add_digits<IterativeSolution>();
    test_add_digits<ConstantSolution>();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
