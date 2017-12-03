// Leetcode: https://leetcode.com/problems/split-array-into-consecutive-subsequences/description/
// Given a sorted integer array (may contain duplicates), determine if the array can be split into
// two or more subsequences of at least 3 consecutive integers.

// Brute Force: Iterate the array, building sequences. Store sequences in a hash map, keyed by last item
// in the sequence. When adding a new item, add it to the shortest sequence available. O(n^2) time.
// Better: Don't store actual sequences. Store the number of sequences of length 1, 2 3+ ending in
// a particular value. O(n) time and space.

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>

struct Sequences {
    int len1 = 0;   // count of length 1 sequences
    int len2 = 0;   // count of length 2 sequences
    int len3 = 0;   // count of length >= 3 sequences 
};

using SequenceMap = std::unordered_map<int, Sequences>;

// Accepted. 102ms. Beats 75.28% of submissions, ties 2.81% of submissions.
class Solution {
public:
    bool isPossible(const std::vector<int>& nums) {
        SequenceMap sequences(nums.size()*2);

        for (auto n : nums) {
            auto found = sequences.find(n-1);
            if (found == sequences.end()) {
                ++sequences[n].len1;
            } else {
                if (found->second.len1 > 0) {
                    --found->second.len1;
                    sequences[n].len2++;
                } else if (found->second.len2 > 0) {
                    --found->second.len2;
                    ++sequences[n].len3;
                } else if (found->second.len3 > 0) {
                    --found->second.len3;
                    ++sequences[n].len3;
                }
                if (found->second.len1 == 0 && found->second.len2 == 0 && found->second.len3 == 0) {
                    sequences.erase(found);
                }
            }
        }

        for (auto& s : sequences) {
            if (s.second.len1 > 0 || s.second.len2 > 0) { return false; }
        }
        return true;
    }
};

void test_is_possible() {
    Solution soln;

    assert(soln.isPossible({3,3,3,4,4,4,5,5,5,6}) == true);
    assert(soln.isPossible({1,2,3,3,4,5}) == true);
    assert(soln.isPossible({1,2,3,4,5,6}) == true);
    assert(soln.isPossible({1,2,3,4,5,6,7}) == true);
    assert(soln.isPossible({1,2,3,5,6,7}) == true);
    assert(soln.isPossible({1,2}) == false);
    assert(soln.isPossible({1,2,78}) == false);
    assert(soln.isPossible({1,2,7,8}) == false);
    assert(soln.isPossible({1,2,7,8,9}) == false);
    assert(soln.isPossible({0,1,2,7,8,9}) == true);
    assert(soln.isPossible({4,4,4}) == false);
    assert(soln.isPossible({4,4,4,5}) == false);
    assert(soln.isPossible({4,4,4,5,5}) == false);
    assert(soln.isPossible({4,4,4,5,5,5}) == false);
    assert(soln.isPossible({4,4,4,5,5,5,6}) == false);
    assert(soln.isPossible({4,4,4,5,5,5,6,6}) == false);
    assert(soln.isPossible({4,4,4,5,5,5,6,6,6}) == true);
    assert(soln.isPossible({4,4,4,5,5,5,6,6,6,7}) == true);
    assert(soln.isPossible({4,4,4,5,5,5,6,6,6,7,7}) == true);
    assert(soln.isPossible({4,4,4,5,5,5,6,6,6,7,7,7}) == true);
    assert(soln.isPossible({4,4,4,5,5,5,6,6,6,7,7,7,7}) == false);
}

int main(int argc, char** argv) {
    test_is_possible();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
