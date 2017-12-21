// Leetcode: https://leetcode.com/problems/task-scheduler/description/
//

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <iostream>
#include <assert.h>

static const int cNumTasks = 26;
struct TaskCount {
    int count = 0;
    char task = '\0';
    TaskCount(char t, int c): count(c), task(t) {}
};
using TaskCounts = std::vector<TaskCount>;

// Accepted. 93ms. Beats 15.07% of submissions, ties < 1% of submissions.
class Solution {
public:
    void resort(TaskCounts& task_counts, int index) {
        while (index+1 < task_counts.size() && task_counts[index].count < task_counts[index+1].count) {
            std::swap(task_counts[index], task_counts[index+1]);
            ++index;
        }
        if (task_counts.back().count == 0) { task_counts.pop_back(); }
    }

    int leastInterval(const std::vector<char>& tasks, int n) {
        int counts[cNumTasks] = {0};
        int last_index[cNumTasks] = {0};

        for (auto t : tasks ) { counts[t-'A']++; }

        TaskCounts task_counts;
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            last_index[ch-'A'] = -1;
            if (counts[ch-'A'] > 0) {
                task_counts.emplace_back(ch, counts[ch-'A']);
            }
        }
        std::sort(task_counts.begin(), task_counts.end(),
                  [](const TaskCount& c1, const TaskCount& c2) { return c1.count > c2.count; });

        int cpu_interval = 0;
        while (!task_counts.empty()) {
            int i = 0;
            while (i < task_counts.size()) {
                auto task = task_counts[i].task;
                if (last_index[task-'A'] == -1 || (cpu_interval - last_index[task-'A'] - 1) >= n) {
                    --task_counts[i].count;
                    last_index[task-'A'] = cpu_interval;
                    resort(task_counts, i); 
                    break;
                }
                ++i;
            }
            ++cpu_interval;
        }
        return cpu_interval;
    }
};

void test_task_scheduler() {
    Solution soln;

    assert(soln.leastInterval({'A','B','C','A','B'}, 2) == 5);    
    assert(soln.leastInterval({'A','A','A','D','B','C','X'}, 1) == 7);    
    assert(soln.leastInterval({'A','A','A','D','B','C','X'}, 0) == 7);    
    assert(soln.leastInterval({'A','A','A','B','C'}, 1) == 5);    
    assert(soln.leastInterval({'A','A','A','B','C'}, 2) == 7);    
    assert(soln.leastInterval({'A','A','A','A','B','B','C'}, 2) == 10);    
    assert(soln.leastInterval({'A','A','A','B','B','B'}, 2) == 8);    
    assert(soln.leastInterval({'A','B','A'}, 1) == 3);    
    assert(soln.leastInterval({'A','B','A'}, 0) == 3);    
    assert(soln.leastInterval({'A','B','A'}, 2) == 4);    
}

int main(int argc, char** argv) {
    test_task_scheduler();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
