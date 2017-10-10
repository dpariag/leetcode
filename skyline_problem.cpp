// Leetcode: https://leetcode.com/problems/the-skyline-problem/description/
// Given the locations and height of the buildings in a cityscape photo, output the skyline formed 
// by the buildings. For overlapping areas, show the profile of the taller building.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

using Building = std::vector<int>;
using Buildings = std::vector<Building>;
using Skyline = std::vector<std::pair<int, int>>;

const int left_side = 0;
const int right_side = 1;
const int height = 2;

class Solution {
public:
    void add_building(Buildings& existing, Building new_building) {
        std::cout << "Adding " << new_building[left_side] << "," << new_building[right_side] 
                  << "," << new_building[height] << std::endl;
        if (existing.empty() || existing.back()[right_side] < new_building[left_side]) {
            existing.emplace_back(new_building);
        } else {
            // New building overlaps with last existing building
            if (new_building[height] >= existing.back()[height]) {
                auto last = existing.back();
                // New building is taller, so shrink the last building
                existing.back()[right_side] = new_building[left_side];
                if (existing.back()[left_side] == existing.back()[right_side]) {
                    // Last building disappeared
                    existing.pop_back();
                }
                existing.emplace_back(new_building);
                // Re-add rightmost portion of last building
                if (new_building[right_side] < last[right_side] ) {
                    last[left_side] = new_building[right_side];
                    if (last[left_side] < last[right_side]) {
                        existing.emplace_back(last);
                    }
                }
                return;
            } else {
                // New building is shorter
                new_building[left_side] = existing.back()[right_side];
            }
            if (new_building[left_side] < new_building[right_side]) {
                existing.emplace_back(new_building);
            }
        }
    }

    Buildings merge(Buildings& b1, Buildings& b2) {
        Buildings merged;
        int i = 0, j = 0;
        while (i < b1.size() && j < b2.size()) {
            if (b1[i][right_side] < b2[j][left_side]) {
                // b1[i] lies entirely to the left of b2[j]
                add_building(merged, b1[i]);
                ++i;
            } else if (b2[j][right_side] < b1[i][left_side]) {
                // b2[j] lies entirely to the left of b1[i]
                add_building(merged, b2[j]);
                ++j;
            } else {
                // Buildings overlap
                Building& left = b1[i], &right = b2[j];
                if (b1[i][left_side] > b2[j][left_side]) {
                    left = b2[j]; right = b1[i];
                }

                if (left[left_side] < right[left_side]) {
                    // Add left portion of left building 
                    add_building(merged, Building({left[left_side],right[left_side],left[height]}));
                }

                // Add taller building during overlap
                add_building(merged, Building({right[left_side],
                            std::min(left[right_side], right[right_side]),
                            std::max(left[height], right[height])}));

                // Add any fragment to the right of the overlap
                if (left[right_side] < right[right_side]) {
                    std::cout << "**Add " << left[right_side] << "," << right[right_side] << "," << right[height] << std::endl;
                    add_building(merged, Building({left[right_side], right[right_side],
                                right[height]}));
                } else if (right[right_side] < left[right_side]) {
                    add_building(merged, Building({right[right_side], left[right_side],
                                left[height]}));
                }
                ++i, ++j;
            }
        }
        while (i < b1.size()) { add_building(merged, b1[i++]); }
        while (j < b2.size()) { add_building(merged, b2[j++]); }
        return merged;
    }

    Buildings mergesort(Buildings& buildings, int start, int end) {
        if (start > end) { return Buildings(); }
        if (start == end) {
            return Buildings(1, buildings[start]);
        }
        int mid = start + (end - start) / 2;
        auto left = mergesort(buildings, start, mid);
        auto right = mergesort(buildings, mid+1, end);

        Buildings merged = merge(left, right);
        return merged;
    }

    Skyline getSkyline(Buildings& buildings) {
        if (buildings.empty()) { return Skyline(); }
        auto merged = mergesort(buildings, 0, buildings.size() - 1);
        Skyline skyline;
        int end = 0;
        for (const auto& m : merged) {
            std::cout << "Merging " << m[left_side] << "," << m[right_side] << "," << m[height] << std::endl;
            std::cout << "end = " << end << std::endl;
            if (skyline.empty()) {
                skyline.emplace_back(std::make_pair(m[left_side], m[height]));
            } else if (skyline.back().second != m[height]) {
                if (end < m[left_side]) {
                    skyline.emplace_back(std::make_pair(end, 0));
                }
                if (m[height] > skyline.back().second) {
                    skyline.emplace_back(std::make_pair(m[left_side], m[height]));
                } else {
                    skyline.emplace_back(std::make_pair(end, m[height]));
                }
            }
            end = m[right_side];
        }
        skyline.emplace_back(end, 0);
        return skyline;
    }
};

bool test_skyline_problem(Buildings buildings, Skyline expected) {
    Solution soln;
    auto skyline = soln.getSkyline(buildings);
    std::cout << "Printing the skyline..." << std::endl;
    for (auto s : skyline) {
        std::cout << s.first << "," << s.second << std::endl;
    }
    std::cout << std::endl << std::endl;
    return skyline == expected;
}

void test_skyline_problem() {
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
