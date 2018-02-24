// Leetcode: https://leetcode.com/problems/add-and-search-word-data-structure-design/description/

// Options: 
// 1) Insert all (2^m) regexes of each word in a hash map. 
//    Insert is O(2^m), Lookup is O(1). O(2^m*n) space.
// 2) Insert each word in a hash map. During lookup, for each '.' substitute each letter in a-z, 
//    lookup and backtrack. Insert is O(1), Lookup is (26^m), O(n*m) space
// 3) Keep words in a vector. Insert is O(1). Lookup scans words and checks if regex can produce 
//    the word. Lookup is O(n*m) which is bad if n >> m. O(n*m) space.
// 4) Build a trie. Lookup requires special handling for '.' with backtracking. 
//    Lookup is O(26^m) in the worst case, but better average case.

#include <string>
#include <iostream>
#include <assert.h>

// Accepted. 92ms. Beat 47.14% of submissions.
class WordDictionary {
public:
    WordDictionary() {}
    
    void addWord(const std::string& word) {
        TrieNode* cur = &m_root;
        for (auto ch : word) {
            int index = ch - 'a';
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }
        cur->is_word = true;
    }
    
    bool search(const std::string& word) {
        TrieNode* cur = &m_root;
        return backtrack_search(word, 0, cur);
    }

private:
    struct TrieNode {
        TrieNode* children[26] = {nullptr};
        bool is_word = false;
    };
    TrieNode m_root;

    bool backtrack_search(const std::string& word, int index, const TrieNode* node) {
        if (node == nullptr) { return false; }
        if (index == word.size()) { return node->is_word; }

        char ch = word[index];
        if (ch == '.') {
            for (int i = 0; i < 26; ++i) {
                if (node->children[i] != nullptr && 
                    backtrack_search(word, index+1, node->children[i])) {
                    return true;
                }
            }
        } else {
            if (node->children[ch-'a'] == nullptr) { return false; }
            return backtrack_search(word, index+1, node->children[ch-'a']);
        }
        return false;
    }
};

void test_word_dictionary() {
    WordDictionary dict;

    dict.addWord("hello");
    dict.addWord("it");
    assert(dict.search("hello") == true);
    assert(dict.search("hell.") == true);
    assert(dict.search(".ello") == true);
    assert(dict.search("he.lo") == true);
    assert(dict.search("he..o") == true);
    assert(dict.search(".....") == true);
    assert(dict.search("he..ox") == false);
    assert(dict.search("x...o") == false);
    assert(dict.search("it") == true);
    assert(dict.search("i.") == true);
    assert(dict.search(".t") == true);
    assert(dict.search("..") == true);
    assert(dict.search("...") == false);
}

int main(int argc, char** argv) {
    test_word_dictionary();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
