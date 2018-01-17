// Leetcode: https://leetcode.com/problems/student-attendance-record-ii/description/

// Brute Force: Generate all possible strings over {A,L,P} and count acceptable ones. O(n*3^n) time.
// Better: Use dynamic programming to derive count(n) from count(n-1). There are six possible kinds of
// strings depending on if they have an 'A' or not, and if they have 0,1 or 2 trailing L's
// The count of each type over n chars can be derived from the counts of each type over n-1 chars.

#include <vector>
#include <stdint.h>
#include <iostream>
#include <assert.h>

static const int MOD = 1000000007;

// Count different kinds of strings
struct Counts {
    int64_t num0L0A = 1;    // 0 trailing L's, no A's
    int64_t num1L0A = 0;    // 1 trailing L, no A's
    int64_t num2L0A = 0;    // 2 trailing L's, no A's
    int64_t num0L1A = 0;    // 0 trailing L's, 1 A
    int64_t num1L1A = 0;    // 1 trailing L, 1 A
    int64_t num2L1A = 0;    // 2 trailing L's, 2 A's
    int64_t total() const { return num0L0A + num1L0A + num2L0A + num0L1A + num1L1A + num2L1A; }
};

// Accepted. 21ms. Beats 91.98% of submissions, ties < 1% of submissions.
class Solution {
public:
    int checkRecord(int n) {
        if (n == 0) { return 0; }

        Counts prev, next;
        for (int i = 0; i < n; ++i) {
            next.num0L0A = (prev.num0L0A + prev.num1L0A + prev.num2L0A) % MOD; // 0L0A + 'P', 1L0A + 'P', 2L0A + 'P'
            next.num1L0A = (prev.num0L0A) % MOD;    // 0L0A + 'L'
            next.num2L0A = (prev.num1L0A) % MOD;    // 1L0A + 'L'

            next.num0L1A = prev.total() % MOD;      // [0-2]L0A + 'A', [0-2]L1A +'P'
            next.num1L1A = (prev.num0L1A) % MOD;    // 0L1A + 'L'
            next.num2L1A = (prev.num1L1A) % MOD;    // 1L1A + 'L'
            prev = next;
        }
        return next.total() % MOD;
    }
};

void test_check_record() {
    Solution soln;

    assert(soln.checkRecord(0) == 0);
    assert(soln.checkRecord(1) == 3);
    assert(soln.checkRecord(2) == 8);
    assert(soln.checkRecord(3) == 19);
    assert(soln.checkRecord(4) == 43);

}

int main(int argc, char** argv) {
    test_check_record();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
