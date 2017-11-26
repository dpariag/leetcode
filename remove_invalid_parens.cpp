// Leetcode: https://leetcode.com/problems/remove-invalid-parentheses/description/
// Given a string of parens and some letters, remove the minimum number of parens to make the 
// input string balanced (ignoring letters). Return all possible balanced strings.

// Brute Force:
// Better:

#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <assert.h>

struct Block {
    std::string str;
    int offset;
    Block(const std::string& s, int o): str(s), offset(o) {}
};

using Queue = std::deque<Block>;
using Strings = std::vector<std::string>;
using StringSet = std::unordered_set<std::string>;

// Accepted. 3ms. Beats 59.72% of submissions, ties 29.15% of submissions.
class Solution {
public:
    void bfs(const std::string& s, StringSet& set, char open, char close) {
        Queue q;

        q.emplace_back("", 0);
        while (!q.empty()) {
            auto block = q.front();
            q.pop_front();
            int i = block.offset, num_open = 0;
            for (; i < s.size(); ++i) {
                block.str.append(1, s[i]);
                if (s[i] == open) { ++num_open; }
                if (s[i] == close) { --num_open; }

                if (num_open < 0) {
                    // Mismatch: Too many closed parens
                    int j = block.str.size() - 1;
                    bool remove = true;
                    while (j >= 0) {
                        if (remove && block.str[j] == close) {
                            q.emplace_back(block.str.erase(j, 1), i+1);
                            block.str.insert(j, 1, close);
                            remove = false;
                        } else if (!remove && block.str[j] != close) {
                            remove = true;
                        }
                        --j;
                    }
                    break;
                }
            } // for

            std::string reverse = block.str;
            std::reverse(reverse.begin(), reverse.end());
            if (num_open == 0) {
                open == '(' ? set.emplace(block.str) : set.emplace(reverse);
            } else if (num_open > 0) {
                bfs(reverse, set, close, open);
            }
        }
    }

    Strings removeInvalidParentheses(std::string& s) {
        StringSet set; 
        Strings result;
        bfs(s, set, '(', ')');
        for (auto& str: set) {
            result.emplace_back(str);
        }
        return result;
    }
};

bool test_remove_invalid(std::string s, Strings expected) {
    Solution soln;
    auto balanced = soln.removeInvalidParentheses(s);
    
    std::sort(balanced.begin(), balanced.end());
    std::sort(expected.begin(), expected.end());
    return balanced == expected;
}

void test_remove_invalid() {
    assert(test_remove_invalid("", {""}));
    assert(test_remove_invalid(")", {""}));
    assert(test_remove_invalid("(", {""}));
    assert(test_remove_invalid("()", {"()"}));
    assert(test_remove_invalid("(()y", {"()y"}));
    assert(test_remove_invalid("p(r)", {"p(r)"}));
    assert(test_remove_invalid("()(())", {"()(())"}));
    assert(test_remove_invalid("(a(()", {"a()", "(a)"}));
    assert(test_remove_invalid("()((()(())", {"()()(())", "()((()))", "()(()())"}));
    assert(test_remove_invalid("((()", {"()"}));
    assert(test_remove_invalid("()())", {"(())", "()()"}));
    assert(test_remove_invalid("(()))", {"(())"}));
    assert(test_remove_invalid("((a)))", {"((a))"}));
    assert(test_remove_invalid("(a()))", {"(a())"}));
    assert(test_remove_invalid("(()a))", {"(()a)", "((a))"}));
    assert(test_remove_invalid("()()())", {"(()())", "()(())", "()()()"}));
}

int main(int argc, char** argv) {
    test_remove_invalid();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
