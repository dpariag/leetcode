// Leetcode: https://leetcode.com/problems/queue-reconstruction-by-height/description/
// People form a queue and are represented by pairs (h, k) where h is the person's height
// and k is the number of people of equal or greater height ahead of them in the queue.
// Can you reconstruct the queue if people are shuffled?

// Brute Force: Compute all permutations of queue, check which ones satisfy the height constraint.
// Better: Sort the queue by descending height, breaking ties using smaller h values.
// Then iterate the sorted queue, inserting people by their k-value. This allows us to insert
// the next tallest person who has the fewest people ahead of them

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Person = std::pair<int,int>; // height, # of taller ahead (k)
using Queue = std::vector<Person>;

// Accepted. 29ms. Beats 98.11% of submissions, ties 1.66% of submissions.
class Solution {
public:
    Queue reconstructQueue(Queue& people) {
        // Sort by decreasing height, breaking ties by smaller k
        std::sort(people.begin(), people.end(),
                  [](const Person& p1, const Person& p2) { return (p1.first > p2.first) || 
                    ((p1.first == p2.first) && (p1.second < p2.second));});
        // Now insert people using their k-value
        Queue q;
        for (const Person& p : people) {
            q.insert(q.begin() + p.second, p);
        }
        return q;
    }
};

bool test_reconstruct(Queue people, Queue expected) {
    Solution soln;

    auto reconstructed = soln.reconstructQueue(people);
    return reconstructed == expected;
}

void test_reconstruct() {
    assert(test_reconstruct({{5,0}}, {{5,0}}));
    assert(test_reconstruct({{5,0},{6,0}}, {{5,0},{6,0}}));
    assert(test_reconstruct({{6,0},{5,0}}, {{5,0},{6,0}}));
    assert(test_reconstruct({{6,0},{5,0},{2,2},{6,1}}, {{5,0},{6,0},{2,2},{6,1}}));
    assert(test_reconstruct({{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}}, 
                            {{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}}));
    assert(test_reconstruct({{12,0},{11,1},{12,2},{13,0}}, 
                            {{12,0},{11,1},{13,0},{12,2},}));
}

int main(int argc, char** argv) {
    test_reconstruct();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
