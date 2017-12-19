// Leetcode: https://leetcode.com/problems/frog-jump/description/
// A frog is crossing a river using stones. Given a sorted list of stones' positions, determine if 
// the frog can reach the last stone. The first jump must be 1 unit, and if the previous jump was 
// k units, the next jump can be k-1, k, or k+1 units. 

// Brute Force:
// Better:

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <assert.h>

using Table = std::vector<std::vector<bool>>;
using Indices = std::unordered_map<int,int>;
using Stones = std::vector<int>;

// Accepted. 716ms. Beats 9.60% of submissions, ties < 1% of submissions.
class Solution {
public:
    bool canCross(const std::vector<int>& stones) {
        if (stones.size() <= 1) { return true; }
        Indices indices;
        for (int i = 0; i < stones.size(); ++i) { indices.emplace(stones[i], i); }
        Table reachable(stones.size(), std::vector<bool>(stones.size() + 1, false));

        reachable[0][0] = true;
        for (int index = 1; index < stones.size(); ++index) {
            for (int jump = 1; jump < stones.size(); ++jump) {
                auto found = indices.find(stones[index] - jump);
                if (found != indices.end()) {
                    reachable[index][jump] = reachable[found->second][jump-1] ||
                                             reachable[found->second][jump] ||
                                             reachable[found->second][jump+1];
                }
                if (index == int(stones.size()) - 1 && reachable[index][jump]) {
                    return true;
                }
            }
        }
        return false;
    }
};

void test_can_cross() {
    Solution soln;
    assert(soln.canCross({1}) == true);
    assert(soln.canCross({0,1,3,5,6,8,12,17}) == true);
    assert(soln.canCross({0,1,2,3,4,8,9,11}) == false);
    assert(soln.canCross({0,1,3,6,10,13,15,16,19,21,25}) == false);
    assert(soln.canCross({0,1,3,6,10,13,15,18}) == true);
}

int main(int argc, char** argv) {
    test_can_cross();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
