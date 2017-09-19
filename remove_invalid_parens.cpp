// Leetcode: 
// Given a string of parens and some letters, remove the minimum number of parens to make the 
// input string balanced (ignoring letters). Return all possible balanced strings.

// Brute Force:
// Better:

#include <vector>
#include <stack>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

class Solution {
public:
#if 0
    inline int next_index(const std::string& s, const std::vector<int>& indices, int cur_idx) {
        int distance = 0;
        for (int i = cur_idx+1; i < indices.size(); ++i) {
            ++distance;
            if (indices[i] > indices[cur_idx] + distance || s[indices[i]] != s[indices[cur_idx]]) {
               return i;
            }
        }
        return int(indices.size());
    }
#endif

    void generate_balanced(Strings& result, std::string& s, 
                           const std::vector<int>& indices, int idx) {

        if (idx == indices.size()) {
            result.emplace_back(s);
            return;
        }

        int s_idx = indices[idx];
        if (s[s_idx] == '(') {
            /*
            s.erase(s_idx, 1);
            generate_balanced(result, s, indices, idx+1); 
            s.insert(s_idx, 1, '(');

            // Skip adjacent '('s, since removing them yields duplicates 
            int j = s_idx+1;
            while (j < s.size() && s[j] == s[s_idx]) { ++j; }
*/
            int j = s_idx+1;
            // Can remove any (non-adjacent) '(' that lies to the right of s[i], then recurse.
            for (; j < s.size(); ++j) {
                if (s[j] == '(') {
                    s.erase(j, 1);
                    generate_balanced(result, s, indices, idx+1); 
                    s.insert(j, 1, '(');
                }
            }
        } else if (s[s_idx] == ')') {
            // Remove the unbalanced ')'
            /*
            s.erase(s_idx, 1);
            generate_balanced(result, s, indices, idx+1);
            s.insert(s_idx, 1, ')');

            // Skip adjacent ')'s, since removing them yields duplicates
            int j = s_idx-1;
            while (j >= 0 && s[j] == s[s_idx]) { --j; }
            */
            int j = s_idx-1;
            // Can remove (non-adjacent) ')'s that lie to the left of s[s_idx], then recurse
            for (; j >= 0; --j) {
                if (s[j] == ')') {
                    s.erase(j, 1);
                    generate_balanced(result, s, indices, idx+1);
                    s.insert(j, 1, ')');
                }
            }
        }
    }

    Strings removeInvalidParentheses(std::string& s) {
        std::vector<int> indices;
        std::cout << "s = " << s << std::endl;

        // Leading ')'s must always be removed.
        while (!s.empty() && s.front() == ')') { s.erase(0, 1); }

        // Trailing '('s must always be removed.
        while (!s.empty() && s.back() == '(') { s.pop_back(); }

        // Use a stack to find unmatched parens
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                indices.push_back(i);
            } else if (s[i] == ')') {
                if (!indices.empty()) {
                    indices.pop_back();
                } else {
                    indices.push_back(i); 
                }
            }
        }
#if 1
        std::vector<int> non_consecutive_indices;
        for (int i = 0; i < indices.size(); ++i) {
            if (i == 0) {
               non_consecutive_indices.emplace_back(indices[i]);
            } else if (indices[i] == indices[i-1] + 1 && s[indices[i]] == s[indices[i-1]]) {
                s.erase(indices[i],1);
                continue;
            } else {
               non_consecutive_indices.emplace_back(indices[i]);
            }
        }
#endif
        for (auto i : non_consecutive_indices) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        std::cout << s << std::endl;
        std::cout << "*************" << std::endl;

        Strings balanced;
        generate_balanced(balanced, s, non_consecutive_indices, 0);
        for (auto& b : balanced) {
            std::cout << b << " ";
        }
        std::cout << std::endl;
        return balanced;
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
    std::string s = "((()()";

    assert(test_remove_invalid("((()()", {"()()", "(())"}));
    assert(test_remove_invalid("()())()", {"(())()", "()()()"}));
    assert(test_remove_invalid("()((", {"()"}));
    assert(test_remove_invalid("(((", {""}));
    assert(test_remove_invalid("()()(()", {"()()()"}));
    assert(test_remove_invalid("()((()(())", {"()()(())", "()((()))"}));
    //assert(test_remove_invalid("(()(()", {"()()"}));
    //assert(test_remove_invalid("", {"", ""}));
}

int main(int argc, char** argv) {
    test_remove_invalid();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
