// Leetcode: https://leetcode.com/problems/binary-watch/description/

// Approach: 4 bits for hour, six bits for minute. For each of the 10 bits, either set it or don't and recurse.
// Recursion terminates when there are no bits left to set.
// Always try to set an hour bit, if that's not possible then set a minute bit. O(2^n) in the worst case.

#include <vector>
#include <iostream>
#include <assert.h>

using Times = std::vector<std::string>;

// Accepted. 0ms. Beats 46.05% of submissions, ties 53.95% of submissions.
class Solution {
public:
    void gen_times(int hour, int hour_shift, int min, int min_shift, int num_bits, Times& times) {
        if (num_bits == 0) {
            if (hour <= 11 && min <= 59) {
                std::string time(std::to_string(hour));
                time.append(":");
                if (min < 10) time.append("0");
                time.append(std::to_string(min));
                times.emplace_back(time);
            }
            return;
        }

        if (hour_shift >= 0) {
            gen_times(hour | (1<<hour_shift), hour_shift-1, min, min_shift, num_bits-1, times);
            gen_times(hour, hour_shift-1, min, min_shift, num_bits, times);
        } else if (min_shift >= 0) {
            gen_times(hour, hour_shift, min | (1 << min_shift), min_shift-1, num_bits-1, times);
            gen_times(hour, hour_shift, min, min_shift-1, num_bits, times);
        }
    }

    Times readBinaryWatch(int num) {
        Times times;
        gen_times(0, 3, 0, 5, num, times);
        return times;
    }
};

void test_binary_watch() {
    Solution soln;
    auto times = soln.readBinaryWatch(1);
    for (auto t : times) { std::cout << t << std::endl; }
}

int main(int argc, char** argv) {
    test_binary_watch();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
