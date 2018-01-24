// Leetcode: https://leetcode.com/problems/the-skyline-problem/description/
// Given the locations and height of the buildings in a cityscape photo, output the skyline formed 
// by the buildings. For overlapping areas, show the profile of the taller building.

// Brute Force:
// Better:

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <assert.h>

const int left_side = 0;
const int right_side = 1;
const int height = 2;

using KeyPoint = std::pair<int, int>;
using Building = std::vector<int>;          // [right, left, height]
using Buildings = std::vector<Building>;
using Skyline = std::vector<KeyPoint>;      // [x,y]

struct Endpoint {
    int index = 0;          // index of the building in the original array
    int x = 0;              // x-cood of the endpoint
    int h = 0;              // height of the building
    bool is_start = true;   // true if the endpoints is a left side
    Endpoint(int i, int pos, int height, bool start): index(i), x(pos), h(height), is_start(start) {}
    bool operator<(const Endpoint& other) const {
        if (x < other.x) { return true; }
        if (x == other.x) {
            if (h > other.h) { return true; } // prefer taller buildings
            if (is_start && !other.is_start) { return true; }
        }
        return false;
    }
};

// Accepted. 27ms. Beats 41.30% of submissions, ties < 1% of submissions.
class Solution {
public:
    Skyline getSkyline(Buildings& buildings) {
        // Build a sorted list of endpoints
        std::vector<Endpoint> endpoints;
        endpoints.reserve(buildings.size()*2);

        for (int i = 0; i < buildings.size(); ++i) {
            endpoints.emplace_back(i, buildings[i][left_side], buildings[i][height], true);
            endpoints.emplace_back(i, buildings[i][right_side], buildings[i][height], false);
        }
        std::sort(endpoints.begin(), endpoints.end());

        // Iterate the sorted endpoints
        auto shorter = [](const Building& b1, const Building& b2) {
            return b1[height] < b2[height] || (b1[height] == b2[height] && b1[right_side] < b2[right_side]);};

        std::priority_queue<Building, std::vector<Building>, decltype(shorter)> tallest(shorter);
        Skyline result;

        for (int i = 0; i < endpoints.size(); ++i) {
            auto& ep = endpoints[i];
            auto& building = buildings[ep.index];

            if (ep.is_start) {
                // New building starting
                if (tallest.empty() || building[height] > tallest.top()[height]) {                    
                    result.emplace_back(std::make_pair(building[left_side], building[height]));
                }
                tallest.emplace(building);
            } else {
                // Building ending
                if (!tallest.empty() && tallest.top() == buildings[ep.index]) {
                    // The ended building is the tallest one
                    tallest.pop();
                    // Remove any shorted buildings that have also ended
                    while(!tallest.empty() && tallest.top()[right_side] <= ep.x) { tallest.pop(); }

                    result.emplace_back(std::make_pair(ep.x, (tallest.empty() ? 0 : tallest.top()[height])));
                }
            }
        }
        return result;
    }
};


bool test_skyline_problem(Buildings buildings, Skyline expected) {
    Solution soln;
    auto skyline = soln.getSkyline(buildings);
    return skyline == expected;
}

void test_skyline_problem() {
    assert(test_skyline_problem({{1,2,1},{1,2,2},{1,2,3}}, {{1,3},{2,0}}));
    assert(test_skyline_problem({{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}},
                                {{2,10}, {3,15}, {7,12},{12,0},{15,10}, {20,8}, {24,0}}));
    assert(test_skyline_problem({{2,13,10},{10,17,25},{12,20,14}},
                {{2,10},{10,25},{17,14},{20,0}}));
}

int main(int argc, char** argv) {
    test_skyline_problem();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}