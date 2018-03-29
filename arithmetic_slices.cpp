// Leetcode: https://leetcode.com/problems/arithmetic-slices/description/

// Brute Force: Count slices starting at each index. O(n^2) time.
// Better: Realize that a slice of length m yields m(m+1)/2 slices whose lengths are
// 1,2,...,m. Thus, scan the array looking for longest possible slices and then calculate
// the number of shorter slices. O(n) time.

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 4ms. Beats 63.96% of submissions.
class Solution {
public:
    // Count the number of slices that exist in a slice of length len
    // There are (len-2) slices of length 3, (len-3) slices of length 4, ... , 1 slice of length len
    inline int count_num_slices(int len) {
        if (len >= 3) {
            int slice_3 = (len - 2);  // number of slices of length 3
            return (slice_3*(slice_3+1)/2); // 3_slices + 4_slices + ...
        }
        return 0;
    }

    int numberOfArithmeticSlices(std::vector<int>& A) {
        if (A.size() < 3) { return 0; }

        int num_slices = 0;
        int len = 2, distance = A[1] - A[0];
        for (int i = 2; i < A.size(); ++i) {
            if (A[i] - A[i-1] == distance) {
                ++len;
            } else {
                num_slices += count_num_slices(len);
                len = 2;
                distance = A[i] - A[i-1];
            }
        }
        num_slices += count_num_slices(len);
        return num_slices;
    }
};

bool test_arithmetic_slices(std::vector<int> A, int expected) {
    Solution soln;
    return soln.numberOfArithmeticSlices(A) == expected;
}

void test_arithmetic_slices() {
    assert(test_arithmetic_slices({1,2}, 0));
    assert(test_arithmetic_slices({1,2,3}, 1));
    assert(test_arithmetic_slices({1,2,3,4}, 3));
    assert(test_arithmetic_slices({1,2,3,4,10,16}, 4));
    assert(test_arithmetic_slices({1,2,3,4,10,16,22}, 6));
    assert(test_arithmetic_slices({1,2,3,4,-1,4,10,16,22}, 6));
}

int main(int argc, char** argv) {
    test_arithmetic_slices();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}