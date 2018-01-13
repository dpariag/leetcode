// Leetcode: https://leetcode.com/problems/exclusive-time-of-functions/description/

// Approach: Use a stack to track the currently executing function.
// When a new function is started, update the running time of the previously running function.
// When a function completes, update it's running time and resume its predecessor (if any) 
// O(n) time and space

#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

struct FuncTime {
    int func_id = -1;
    int total_time = 0;
    int resumed = 0;    // start of the interval the function was resumed.
    FuncTime(int f, int t, int r): func_id(f), total_time(t), resumed(r) {}
};

// Accepted. 27ms. Beats 64.70% of submissions, ties < 1% of submissions.
class Solution {
public:
    std::vector<int> exclusiveTime(int n, const std::vector<std::string>& logs) {
        std::vector<int> times(n, 0);
        std::stack<FuncTime> stack;

        for (auto& log : logs) {
            int index1 = log.find(':', 0);
            int index2 = log.find(':', index1+1);

            int func_id = std::stoi(log.substr(0, index1));
            std::string op = log.substr(index1+1, index2 - index1 - 1);
            int timestamp = std::stoi(log.substr(index2+1, log.size()));

            if (op.front() == 's') {
                if (!stack.empty()) {
                    auto& top = stack.top();
                    top.total_time += (timestamp - top.resumed);
                }
                stack.emplace(func_id, 0, timestamp);
            } else if (op.front() == 'e') {
                if (!stack.empty()) {
                    auto& top = stack.top();
                    top.total_time += (timestamp - top.resumed + 1);
                    times[top.func_id] += top.total_time;
                    stack.pop();
                    if (!stack.empty()) {
                        stack.top().resumed = timestamp + 1;
                    }
                }
            }
        }
        return times;
    }
};

void test_exclusive_time() {
    Solution soln;

    assert(soln.exclusiveTime(4, {"0:start:0","1:start:2", "1:end:5", "2:start:6", "3:start:7", "3:end:8", "2:end:9", "0:end:10"}) == std::vector<int>({3,4,2,2}));
}

int main(int argc, char** argv) {
    test_exclusive_time();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
