// Leetcode: https://leetcode.com/problems/simplify-path/description/
// Given an absolute path for a file (Unix-style), simplify it.
// For example: "/home/", -> "/home" and "/a/./b/../../c/", -> "/c"

// Brute Force:
// Better:

#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 3ms. Beats 97.69% of submissions, ties 2.31% of submissions
class Solution {
public:
    std::string simplifyPath(std::string& path) {
        std::vector<std::string> stack; // use a vector as a stack
        std::string elem;

        path.append(1, '/');
        for (int i = 0; i < int(path.size()); ++i) {
            char ch = path[i];
            if (ch == '/') {
                if (elem == ".." && !stack.empty()) {
                    stack.pop_back(); 
                } else if (!elem.empty() && elem != "." && elem != "..") {
                    stack.push_back(elem);                    
                }
                elem.clear();
                continue;
            }
            elem.push_back(ch);
        }

        std::string result = "/";
        for (int i = 0; i < int(stack.size()); ++i) {            
            result.append(stack[i]);
            if (i != int(stack.size()) -1) result.append(1, '/');
        }
        path.pop_back();
        return result;
    }
};

bool test_simplify_path(std::string path, std::string simplified) {
    Solution soln;
    return soln.simplifyPath(path) == simplified;
}

void test_simplify_path() {
    assert(test_simplify_path("/", "/"));
    assert(test_simplify_path("/..", "/"));
    assert(test_simplify_path("//", "/"));
    assert(test_simplify_path("//.", "/"));
    assert(test_simplify_path("/././.", "/"));
    assert(test_simplify_path("/b/../.", "/"));
    assert(test_simplify_path("/b/../c", "/c"));
    assert(test_simplify_path("/b/c", "/b/c"));
    assert(test_simplify_path("/b//c", "/b/c"));
    assert(test_simplify_path("/b/c/", "/b/c"));
    assert(test_simplify_path("///b/c//", "/b/c"));
    assert(test_simplify_path("/b/c/../././d", "/b/d"));
    assert(test_simplify_path("/b/c/../././d/e/f/../g", "/b/d/e/g"));
    assert(test_simplify_path("/foo/bar/../././/bar/s/../gone", "/foo/bar/gone"));
}

int main(int argc, char** argv) {
    test_simplify_path();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}

