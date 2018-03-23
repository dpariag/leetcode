// Leetcode: https://leetcode.com/problems/minimum-genetic-mutation/description/

// Approach: Treat genes in the bank as the vertices of a graph. 
// Then use breadth-first-search from the starting string, trying to reach the destination string.
// O(V+E) time/space

#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <assert.h>

struct Entry {
    std::string cur;
    int mutations;
    Entry(const std::string& c, int m): cur(c), mutations(m) {}
};

using Queue = std::queue<Entry>;
using Dictionary = std::unordered_set<std::string>;
using Strings = std::vector<std::string>;

// Accepted. Beats 51.23% of submissions, ties 43.35% of submissions.
class Solution {
public:
    int minMutation(const std::string& start, const std::string& end, Strings& bank) {
        const char symbols[4] = {'A', 'C', 'G', 'T'};
        Dictionary dict(bank.begin(), bank.end());
        Queue q;

        q.emplace(start, 0);
        dict.erase(start);

        while (!q.empty()) {
            auto entry = q.front();
            if (entry.cur == end) { return entry.mutations; }

            for (int i = 0; i < entry.cur.size(); ++i) {
                char prev = entry.cur[i];
                for (int j = 0; j < 4; ++j) {
                    if (symbols[j] == prev) continue;
                    entry.cur[i] = symbols[j];
                    if (dict.count(entry.cur)) {
                        q.emplace(entry.cur, entry.mutations+1);
                        dict.erase(entry.cur);
                    }    
                }
                entry.cur[i] = prev;
            }
            q.pop();
        }
        return -1;
    }
};

bool test_min_mutations(std::string start, std::string end, Strings bank, int expected) {
    Solution soln;
    return soln.minMutation(start, end, bank) == expected;
}

void test_min_mutations() {
    assert(test_min_mutations("ACT", "TCG", {"GCT", "GCG", "TCG"}, 3));
    assert(test_min_mutations("AACCGGTT", "AACCGGTA", {"AACCGGTA"}, 1));
    assert(test_min_mutations("AACCGGTT", "AAACGGTA", {"AACCGGTA", "AACCGCTA", "AAACGGTA"}, 2));
    assert(test_min_mutations("AAAAACCC", "AACCCCCC", {"AAAACCCC", "AAACCCCC", "AACCCCCC"}, 3));
}

int main(int argc, char** argv) {
    test_min_mutations();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
