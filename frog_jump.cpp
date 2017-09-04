// Leetcode: https://leetcode.com/problems/frog-jump/description/
// A frog is crossing a river using stones. Given a sorted list of stones' positions, determine if 
// the frog can reach the last stone. The first jump must be 1 unit, and if the previous jump was 
// k units, the next jump can be k-1, k, or k+1 units. 

// Brute Force:
// Better:

#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <assert.h>

struct Stone {
    int position;
    int last_jump;
    Stone(int p, int l) : position(p), last_jump(l) {}
};

class Solution {
public:
    bool canCross(const std::vector<int>& stones) {
        if (stones.size() <= 1) { return true; }
        std::unordered_set<int> stones_set(stones.begin(), stones.end());
        std::queue<Stone> q;
        q.emplace(Stone(stones[0], 0));

        while (!q.empty()) {
            auto stone = q.front();
            q.pop();

            for (int jump : {stone.last_jump - 1, stone.last_jump, stone.last_jump+1}) {
                if (jump <= 0) { continue; }
                int next_position = stone.position + jump;
                if (next_position == stones.back()) { return true; }
                if (stones_set.count(next_position)) {
                    q.emplace(Stone(next_position, jump));
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
}

int main(int argc, char** argv) {
    test_can_cross();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
