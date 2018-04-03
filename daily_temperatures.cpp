// Leetcode: https://leetcode.com/problems/daily-temperatures/description/
// Given an array of daily temps, find the number of days you have to wait (each day)
// before a warmer day arrives.

// Brute Force: For each temp, scan forward looking for a larger one. O(n^2) time.
// Better: Use a stack to store indices of cooler temps. Each time a temp is processed,
// pop of any cooler temps and calculate the number of intervening days.

#include <vector>
#include <iostream>
#include <assert.h>

using Temperatures = std::vector<int>;

// Accepted. 229ms. Beats 94.48% of submissions.
class Solution {
public:
    Temperatures dailyTemperatures(Temperatures& temps) {
        Temperatures warmer(temps.size(), 0);
        std::vector<int> indices;
        indices.reserve(temps.size());

        for (int i = 0; i < temps.size(); ++i) {
            while (!indices.empty() && temps[indices.back()] < temps[i]) {                
                warmer[indices.back()] = (i - indices.back());
                indices.pop_back();
            }
            indices.emplace_back(i);
        }

        while (!indices.empty()) {
            warmer[indices.back()] =  0;
            indices.pop_back();
        }
        return warmer;
    }
};

bool test_daily_temps(Temperatures temps, std::vector<int> expected) {
    Solution soln;
    return soln.dailyTemperatures(temps) == expected;
}

void test_daily_temps() {
    assert(test_daily_temps({30}, {0}));
    assert(test_daily_temps({73,72,71,70}, {0,0,0,0}));
    assert(test_daily_temps({73,74,75,76}, {1,1,1,0}));
    assert(test_daily_temps({73,73,73,73}, {0,0,0,0}));
    assert(test_daily_temps({73,74,75,71,69,72,76,73}, {1,1,4,2,1,1,0,0}));
}

int main(int argc, char** argv) {
    test_daily_temps();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
