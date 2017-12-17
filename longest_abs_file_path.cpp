// Leetcode: https://leetcode.com/problems/longest-absolute-file-path/description/
// Given a filesystem represented as a string, find the longest pathname to a file in the system.
// The string:
// "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" 
// represents:
// dir
//     subdir1
//             file1.ext
//             subsubdir1
//    subdir2
//      subsubdir2
//                file2.ext

// Approach: Scan the string using a stack to store the current path. The indentation level
// of each line determines if we push/pop the stack. O(n) time and space.

#include <stack>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 1.16% of submissions, ties 74.01% of submissions.
class Solution {
public:
    int lengthLongestPath(const std::string& input) {
        std::stack<std::string> stack;
        int pos = 0, longest_path = 0, cur_path = 0;

        while (pos < input.size()) {
            int next = input.find('\n', pos);
            if (next == std::string::npos) { next = input.size(); }

            int scan = pos;
            while (scan < input.size() && input[scan] == '\t') { ++scan; }
            int num_tabs = scan - pos;

            while (stack.size() > num_tabs) {
                cur_path -= stack.top().size();
                stack.pop();
            }

            stack.push(input.substr(scan, next-scan));
            cur_path += stack.top().size();

            if (stack.top().find('.') != std::string::npos) {
                longest_path = std::max(longest_path, (cur_path + int(stack.size()) - 1));
            }
            pos = next + 1;
        }
        return longest_path;
    }
};

void test_longest_path() {
    Solution soln;

    assert(soln.lengthLongestPath("") == 0);
    assert(soln.lengthLongestPath("a") == 0);
    assert(soln.lengthLongestPath("file.txt") == 8);
    assert(soln.lengthLongestPath("dir/file.txt") == 12);
    assert(soln.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext") == 20);
    assert(soln.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") == 32);

}

int main(int argc, char** argv) {
    test_longest_path();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
