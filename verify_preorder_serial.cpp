// Leetcode: https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/description/

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <assert.h>

struct VisitNode {
    std::string key;
    int num_children = 0;
    VisitNode(const std::string& k, int n): key(k), num_children(n) {}
};
using VisitedStack = std::stack<VisitNode>;

// Accepted. 6ms. Beats 17.87% of submissions, ties 48.31% of submissions.
class Solution {
public:
    bool isValidSerialization(const std::string& preorder) {
        if (preorder.empty() || preorder == "#") { return true; }
        VisitedStack stack;
        int i = 0;

        while (i < preorder.size()) {
            int idx = preorder.find(',', i);
            if (idx == std::string::npos) { idx = preorder.size(); }
            std::string key = preorder.substr(i, idx-i);

            if (key == "#") {
                if (stack.empty() || stack.top().num_children >= 2) { return false; }
                stack.top().num_children++;

            } else {
                stack.emplace(key, 0);
            }
            while (!stack.empty() && stack.top().num_children == 2) {
                stack.pop();
                if (!stack.empty()) { stack.top().num_children++; }
            }
            i = idx + 1;
            if (stack.empty() && i < preorder.size()) { return false; }
        }
        return stack.empty();
    }
};

void test_serialization() {
    Solution soln;

    assert(soln.isValidSerialization("9,3,4,#,#,1,#,#,#,2,#,6,#,#") == false);

    assert(soln.isValidSerialization("#") == true);
    assert(soln.isValidSerialization("10,#,#") == true);
    assert(soln.isValidSerialization("10,#") == false);
    assert(soln.isValidSerialization("10,#,#,#") == false);
    assert(soln.isValidSerialization("10,#,#,1") == false);
    assert(soln.isValidSerialization("9,3,#,#,6,8,#,#,#") == true);

    assert(soln.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") == true);
    assert(soln.isValidSerialization("9,#,10,#,11,12,1,#,#,2,#,#,#") == true);
    assert(soln.isValidSerialization("9,#,10,#,11,12,1,#,#,2,#,#") == false);
}

int main(int argc, char** argv) {
    test_serialization();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
