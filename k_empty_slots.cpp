// Leetcode: https://leetcode.com/problems/k-empty-slots/description/
// Given an flower bed with N spots (1..N), flowers[i] = j denotes that on the i'th day, the j'th
// flower will bloom (and stay in bloom thereafter). Given an integer k, determine if there is a
// day where two flowers are in bloom with k empty spots between them.

// Brute Force: Iterate the flowers array (for days 1,2,...N), switching flowers into bloom and 
// checking k flowers away. O(n*k)
// Better: Build the reverse mapping from flowers -> bloom day, then iterate flowers 1...N
// maintaining an interval (left_flower, right_flower) and bloom days (left_day, right_day).
// If the i'th flower blooms before left_day or right_day, then the interval is reset. O(n) time and space.

#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <ctime>
#include <assert.h>

// Accepted. 199ms. Beats 79.86% of submissions, ties 4.66% of submissions.
class Solution {
public:
    int kEmptySlots(const std::vector<int>& flowers, int k) {
        if (flowers.size() < k+2) { return -1; }

        int days[flowers.size()+1] = {0};
        for (int i = 0; i < flowers.size(); ++i) {
            days[flowers[i]] = i+1;
        }

        bool found = false;
        int best_day1 = std::numeric_limits<int>::max(), best_day2 = std::numeric_limits<int>::max();
        int left_flower = 1, left_day = days[left_flower];
        int right_flower = left_flower + k + 1, right_day = days[right_flower];
        for (int flower = 2; flower <= flowers.size(); ++flower) {
            int day = days[flower];

            if (flower == right_flower) {
                if (std::max(left_day, right_day) < std::max(best_day1, best_day2)) {
                    best_day1 = left_day;
                    best_day2 = right_day;
                    found = true;
                }
                left_flower = flower;
                left_day = day;
                right_flower = left_flower + k + 1;
                if (right_flower > flowers.size()) { break; }
                right_day = days[right_flower];
            } else if (day < left_day || day < right_day) {
                left_flower = flower;
                left_day = day;
                right_flower = left_flower + k + 1;
                if (right_flower > flowers.size()) { break; }
                right_day = days[right_flower];
            }
        }
        return found ? std::max(best_day1, best_day2) : -1;
    }
};

void test_k_empty_slots() {
    Solution soln;
    assert(soln.kEmptySlots({1,2,3}, 1) == -1);
    assert(soln.kEmptySlots({3,9,2,8,1,6,10,5,4,7}, 1) == 6);
    assert(soln.kEmptySlots({1,3,2}, 1) == 2);
    assert(soln.kEmptySlots({6,5,8,9,7,1,10,2,3,4}, 2) == 8);
}

int main(int argc, char** argv) {
    test_k_empty_slots();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
