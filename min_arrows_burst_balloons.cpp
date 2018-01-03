// Leetcode: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/
// Given balloons spanning a horizontal distance (x1,x2) on the x-axis, determine the minimum
// number of arrows required to pop all the balloons.

// Brute Force: Scan the entire x-axis, noting at each co-od the balloons hit. O(X), x-axis length
// Better: Sort balloons by starting co-od, then track overlap betw. consecutive balloons O(n*logn)

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Balloon = std::pair<int,int>;
using Balloons = std::vector<Balloon>;

// Accepted. 86ms. Beats 81.72% of submissions, ties 11.83% of submissions.
class Solution {
public:
    int findMinArrowShots(Balloons& balloons) {
        if (balloons.empty()) { return 0; }

        Balloons result;
        std::sort(balloons.begin(), balloons.end(),
                 [](const Balloon&a, const Balloon&b) { return a.first < b.first; });

        result.push_back(balloons.front());
        for (int i = 1; i < balloons.size(); ++i) {
            auto& cur = result.back();
            if (balloons[i].first >= cur.first && balloons[i].first <= cur.second) {
                cur.first = std::max(cur.first, balloons[i].first);
                cur.second = std::min(cur.second, balloons[i].second);
            } else {
                result.push_back(balloons[i]);
            }
        }
        return result.size();
    }
};

bool test_min_arrows(Balloons b, int expected_min_arrows) {
    Solution soln;
    return soln.findMinArrowShots(b) == expected_min_arrows;
}

void test_min_arrows() {
    assert(test_min_arrows({},0));
    assert(test_min_arrows({{2,5},{1,4},{3,4}},1));
    assert(test_min_arrows({{2,5},{1,4},{13,14}},2));
    assert(test_min_arrows({{2,5},{1,4},{13,14},{14,14}},2));
}

int main(int argc, char** argv) {
    test_min_arrows();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
