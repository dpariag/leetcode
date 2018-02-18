// Leetcode: https://leetcode.com/problems/kill-process/description/
// Given a list of parent pids and child pids which form a process tree,
// return all processed which will be killed if a given pid is killed.

// Approach: Use BFS to explore children starting at the killed pid. O(V+E) time/space.

#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using PIDs = std::vector<int>;
using Queue = std::list<int>;
using ChildMap = std::unordered_map<int, Queue>; // pid -> list of children

// Accepted. 188ms. Beats 54.02% of submissions, ties 0.38% of submissions.
class Solution {
public:
    PIDs killProcess(PIDs& pids, PIDs& ppids, int kill) {
        ChildMap child_map;

        for (int i = 0; i < pids.size(); ++i) {
            child_map[ppids[i]].emplace_back(pids[i]);
        }

        Queue q;
        q.emplace_back(kill);

        PIDs killed;
        while (!q.empty()) {
            auto next_kill = q.front();
            q.pop_front();
            q.splice(q.end(), child_map[next_kill]);
            killed.emplace_back(next_kill);
        }
        return killed;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
