// Leetcode: 

// Brute Force:
// Better:

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>
#include <assert.h>

using Words = std::vector<std::string>;
using WordSet = std::unordered_set<std::string>;
using Board = std::vector<std::vector<char>>;
using Visited = std::vector<std::vector<bool>>;

struct TrieNode {
    TrieNode* children[26] = {nullptr};
    bool is_word = false;
};

// Accepted. 45ms. Beats 71.05% of submissions, ties 4.09% of submissions.
class Solution {
public:
    Words findWords(Board& board, Words& dict) {
        WordSet unique_words;
        Visited visited(board.size(), std::vector<bool>(board[0].size(), false));
        
        for (auto& dict_word : dict) { 
            add_word(dict_word);
        }

        for (int row = 0; row < board.size(); ++row) {
            for (int col = 0; col < board[0].size(); ++col){                
                std::string word;
                dfs(board, row, col, &m_trie, visited, word, unique_words);
            }
        }
        return Words(unique_words.begin(), unique_words.end());
    }

private:
    bool dfs(const Board& board, int row, int col, TrieNode* cur, Visited& visited,  std::string& word, WordSet& result) {
        auto ch = board[row][col];
        if (cur == nullptr || cur->children[ch-'a'] == nullptr) { return false; }

        visited[row][col] = true;
        word.append(1, ch);
        if (cur->children[ch-'a']->is_word) { 
            result.emplace(word); // keep going!
        }
        
        std::vector<std::pair<int,int>>neighbors = {{row-1,col}, {row+1,col}, {row,col-1}, {row,col+1}};
        for (auto& n : neighbors) {
            if (n.first >= 0 && n.first < board.size() && n.second >= 0 && n.second < board[0].size()) {
                if (!visited[n.first][n.second]) {
                    dfs(board, n.first, n.second, cur->children[ch-'a'], visited, word, result);
                }
            }
        }

        word.pop_back();
        visited[row][col] = false;
        return false;
    }

    void add_word(const std::string& word) {
        TrieNode* cur = &m_trie;
        for (auto ch: word) {
            if (cur->children[ch-'a'] == nullptr) {
                cur->children[ch-'a'] = new TrieNode();
            }
            cur = cur->children[ch-'a'];
        }
        cur->is_word = true;
    }

    TrieNode m_trie;
};

bool test_word_search(Board board, Words dict, Words expected) {
    Solution soln;

    auto words = soln.findWords(board, dict);
    std::sort(words.begin(), words.end());
    std::sort(expected.begin(), expected.end());
    return words == expected;
}

void test_word_search() {
    assert(test_word_search({{'o','a','r','e'},
                             {'x','t','x','s'},
                             {'y','h','z','t'},
                             {'e','s','t','a'}},
                             {"oath", "hello", "sassy"},
                             {"oath"}));

    assert(test_word_search({{'o','a','r','e'},
                             {'x','t','x','s'},
                             {'y','h','z','t'},
                             {'e','s','t','a'}},
                             {"oath", "hello", "sassy", "oar"},
                             {"oath", "oar"}));
    
    assert(test_word_search({{'o','a','r','e'},
                             {'x','t','x','s'},
                             {'y','h','z','t'},
                             {'e','s','t','a'}},
                             {"oath", "hello", "xyz", "oar","tat"},
                             {"oath", "oar", "tat"}));

    assert(test_word_search({{'o','a','r','e'},
                             {'x','t','x','s'},
                             {'y','h','z','t'},
                             {'e','s','t','a'}},
                             {"oath", "oaths", "yes", "oar","tat"},
                             {"oath", "oaths", "yes", "oar", "tat"}));

}

int main(int argc, char** argv) {
    test_word_search();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
