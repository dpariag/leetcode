// Leetcode: https://leetcode.com/problems/queue-reconstruction-by-height/description/
// People form a queue and are represented by pairs (h, k) where h is the person's height
// and k is the number of people of equal or greater height ahead of them in the queue.
// Can you reconstruct the queue if people are shuffled?

// Brute Force: Compute all permutations of queue, check which ones satisfy the height constraint.
// Better: Sort the queue by descending height, breaking ties using smaller h values.
// Then iterate the sorted queue, inserting people by their h-value. This allows us to insert
// the next tallest person who has the fewest people ahead of them

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

using Person = std::pair<int,int>;
using Queue = std::vector<Person>;

void print(Queue& q) {
    for (int i = 0; i < q.size(); ++i) {
        std::cout << q[i].first << "," << q[i].second << " ";
    }
    std::cout << std::endl;
}

// Start: 10:10am
// Coded: 10:27am
class Solution {
public:

    int num_taller_ahead(Queue& people, int height, int index) {
        int count = 0;
        for (int i = 0; i < index; ++i) {
            if (people[i].first >= height) { ++count; }
        }
        return count;
    }

    Queue reconstructQueue(Queue& people) {
        // Sort by height, breaking ties by k
        std::sort(people.begin(), people.end(),
                  [](const Person& p1, const Person& p2) { return (p1.first < p2.first) || 
                    ((p1.first == p2.first) && (p1.second < p2.second));});

        int i = 0;
        while (i < people.size()) {
            int num_taller = people[i].second;
            int actual_taller = num_taller_ahead(people, people[i].first, i);

            if (actual_taller == num_taller) {
                ++i;
                continue;
            }
        
            std::cout << "actual_taller = " << actual_taller << " but need " << num_taller << std::endl;       
            print(people);
            int cur = i, next = i+1;
            while (actual_taller < num_taller && (next < people.size())) {
                std::swap(people[cur], people[next]);
                print(people);
                if (people[next].first < people[cur].first) { ++actual_taller; }
                cur = next, next++;
            }
            print(people);

            std::cout << "now actual_taller = " << actual_taller << std::endl;       
            assert(actual_taller == num_taller);
        }
        return people;
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
