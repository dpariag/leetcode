// Leetcode: https://leetcode.com/problems/implement-trie-prefix-tree/description/
// Implement a trie with insert, search, and startsWith methods for strings of lowercase letters.

// Brute Force:
// Better:

#include <vector>
#include <iostream>
#include <assert.h>

// Accepted. 58ms. Beats 91.83% of submissions, ties 1.63% of submissions.
class Trie {
public:
    struct Node {
        Node* children[26] = {nullptr};
        bool ends_word = false;
    };

    /** Initialize your data structure here. */
    Trie() {}
    
    /** Inserts a word into the trie. */
    void insert(const std::string& word) {
        // TODO: Empty string?
        int i = 0;
        Node* last = &m_root;
        Node** next = m_root.children;
        while (i < word.size())
        {
            int index = word[i] - 'a';
            if (next[index] == nullptr) {
                next[index] = new Node();
            }
            last = next[index];
            next = next[index]->children;
            ++i;
        }
        last->ends_word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(const std::string& word) {
        Node* last = &m_root;
        Node** next = m_root.children;
        for (auto ch: word) {
            int index = ch - 'a';
            if (next[index] == nullptr) { return false; }
            last = next[index];
            next = next[index]->children;
        }
        return last->ends_word; // Differentiate prefixes from entire words
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const std::string& prefix) {
        Node** next = m_root.children;
        for (auto ch: prefix) {
            int index = ch - 'a';
            if (next[index] == nullptr) { return false; }
            next = next[index]->children;
        }
        return true;
    }

private:
    Node m_root;
};

void test_trie() {
    Trie t;

    assert(t.search("") == false);
    assert(t.startsWith("") == true);
    assert(t.search("hello") == false);

    t.insert("hello");
    assert(t.search("hello") == true);
    assert(t.search("hell") == false);
    assert(t.startsWith("hell") == true);
    assert(t.startsWith("hello") == true);

    t.insert("world");
    assert(t.search("hello") == true);
    assert(t.search("world") == true);
    assert(t.startsWith("w") == true);
    assert(t.search("w") == false);

    t.insert("helloworld");
    assert(t.search("hello") == true);
    assert(t.search("world") == true);
    assert(t.search("helloworld") == true);
    assert(t.startsWith("helloworld") == true);
}

int main(int argc, char** argv) {
    test_trie();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
