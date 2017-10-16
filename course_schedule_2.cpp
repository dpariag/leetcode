// Leetcode: https://leetcode.com/problems/course-schedule-ii/description/
// Given n courses labeled {0, ..., n - 1}, and a list of pre-requisites represented as pairs
// {course, prereq}, return an ordering that allows you to complete all n courses, or the empty
// array if no ordering exists.

// Brute Force: Generate all permutations of courses, check if pre-reqs are satisfied. O(n!) time.
// Better: Represent pre-reqs as a graph. An edge X --> Y means X is a pre-req of Y. Use BFS-like
// traversal to process the deps in the graph. O(#edges) time.

#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

using Courses = std::vector<int>;
using Prereqs = std::vector<std::pair<int, int>>;
using Graph = std::vector<std::vector<int>>; // Adjaceny list

// Accepted. 16ms. Beats 69.00% of submissions, ties 28.62% of submissions.
class Solution {
public:
    Courses findOrder(int numCourses, const Prereqs& prereqs) {
        Courses ordering;
        std::vector<int> num_deps(numCourses, 0);
        Graph deps(numCourses, std::vector<int>()); // for each node, store courses that depend on it

        // Count pre-reqs for each course
        for (int i = 0; i < prereqs.size(); ++i) {
            num_deps[prereqs[i].first]++;
            deps[prereqs[i].second].emplace_back(prereqs[i].first);
        }

        // Do BFS starting from nodes with no deps
        std::list<int> q;
        for (int i = 0; i < num_deps.size(); ++i) {
            if (num_deps[i] == 0) { q.emplace_back(i); }
        }

        while (!q.empty()) {
            auto course = q.front();
            q.pop_front();
            ordering.emplace_back(course);

            for (int i = 0; i < deps[course].size(); ++i) {
                int next_course = deps[course][i];
                num_deps[next_course]--;
                if (num_deps[next_course] == 0) {
                    q.emplace_back(next_course);
                }
            }
        }
        return ordering.size() == numCourses ? ordering : Courses(); 
    }
};

bool test_find_order(int numCourses, Prereqs pre_reqs, Courses expected_order) {
    Solution soln;
    auto order = soln.findOrder(numCourses, pre_reqs);
    return order == expected_order;
}

void test_find_order() {
    assert(test_find_order(2, {{1,0}}, {0,1}));
    assert(test_find_order(2, {{1,0},{0,1}}, {})); // cycle
    assert(test_find_order(2, {{1,0},{0,1},{2,0}}, {})); // cycle
    assert(test_find_order(5, {{0,1},{1,2},{0,3},{1,4}}, {2,3,4,1,0}));
    assert(test_find_order(6, {{5,2},{0,2},{0,3},{0,1},{1,4},{1,5}}, {2,3,4,5,1,0}));
}

int main(int argc, char** argv) {
    test_find_order();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
