// Leetcode: https://leetcode.com/problems/next-closest-time/description/
// Given a time represented in the format "HH:MM", form the next closest future time by reusing the 
// current digits. There is no limit on how many times a digit can be reused.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 0ms. Beats 83.41% of submissions, ties 16.59% of submissions.
class Solution {
public:

    inline int max(const std::string& time, int offset) {
        switch (offset) {
            case 0:
                return 2;
            case 1:
                return time[0] <= '1' ? 9 : 4;
            case 3:
                return 5;
            case 4:
                return 9;
        }
        return 9;
    }

    inline char next(const std::vector<bool>& digits, std::string& time, int offset) {
        int digit = time[offset] - '0';
        for (int i = digit+1; i < digits.size(); ++i) {
            if (digits[i] && i <= max(time, offset)) { return '0' + i; }
        }
        return '0';
    }

    inline char min_digit(const std::vector<bool>& digits) {
        for (int i = 0; i < digits.size(); ++i) {
            if (digits[i]) { return '0' + i; }
        }
        return '9';
    }

    std::string nextClosestTime(std::string time) {
        std::string result = time;
        std::vector<bool> digits(10, false);

        digits[time[0] - '0'] = true;
        digits[time[1] - '0'] = true;
        digits[time[3] - '0'] = true;
        digits[time[4] - '0'] = true;

        int i = 4;
        while (i >=0) {
            if (i != 2) {
                auto next_char = next(digits, time, i);
                if (next_char != '0') {
                    result[i] = next_char;
                    break;
                }
            }
            --i;
        }

        int j = i + 1;
        char min = min_digit(digits);
        while (j < result.size()) {
            if (j != 2) { result[j] = min; }
            ++j;
        }
        return result;
    }
};

void test_next_closest_time() {
    Solution soln;

    assert(soln.nextClosestTime("01:19") == "09:00");
    assert(soln.nextClosestTime("23:59") == "22:22");
    assert(soln.nextClosestTime("22:22") == "22:22");
    assert(soln.nextClosestTime("05:19") == "05:50");
    assert(soln.nextClosestTime("06:59") == "09:00");
    assert(soln.nextClosestTime("05:59") == "09:00");
    assert(soln.nextClosestTime("19:34") == "19:39");
    assert(soln.nextClosestTime("05:10") == "05:11");
}

int main(int argc, char** argv) {
    test_next_closest_time();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
