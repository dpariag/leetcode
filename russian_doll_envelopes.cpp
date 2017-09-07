// Leetcode: https://leetcode.com/problems/russian-doll-envelopes/description/
// Given an array of envelopes represented as (width, height) pairs, find the max number of envelopes
// that can be stuffed one inside the other (inside envelope must be smaller) 

// Brute Force: Generate all permutations of envelopes, check if each is valid. O(n!)
// Better: Sort envelopes by width, then find the longest increasing sequence by height. O(n^2) time.

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Envelope = std::pair<int, int>; // (width, height) of envelope
using Envelopes = std::vector<Envelope>;

// Accepted. 276ms. Beats 51.37% of submissions, ties approx. 1% of submissions.
class Solution {
public:
    int maxEnvelopes(Envelopes& envelopes) {
        std::sort(envelopes.begin(), envelopes.end(), 
                  [](const Envelope& e1, const Envelope& e2) { 
                  return e1.first > e2.first || (e1.first == e2.second && e1.second > e2.second);});

        // max_stuffed[i] holds the length of the largest stuffing ending with envelopes[i]
        std::vector<int> max_stuffed(envelopes.size(), 1);
        int max = 0;
        for (int i = 0; i < envelopes.size(); ++i) {
            int count = 1;
            for (int j = 0; j < i; ++j) {
                if (envelopes[i].first < envelopes[j].first && 
                    envelopes[i].second < envelopes[j].second) {
                    count = std::max(count, max_stuffed[j] + 1);
                }
            }
            max_stuffed[i] = count;
            max = std::max(max, count);
        }
        return max;
    }
};

bool test_max_envelopes(Envelopes envelopes, int expected_max) {
    Solution soln;
    return soln.maxEnvelopes(envelopes) == expected_max;
}

void test_max_envelopes() {
    assert(test_max_envelopes({{5,4},{6,4},{6,7},{2,3}}, 3));
    assert(test_max_envelopes({{10,7},{9,1},{8,2},{9,6},{5,4}, {3,2}}, 4));
}

int main(int argc, char** argv) {
    test_max_envelopes();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
