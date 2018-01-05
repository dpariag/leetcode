// Leetcode: https://leetcode.com/problems/encode-and-decode-tinyurl/description/

// Approach: Create a two-way mapping from a URL to a six-character identifier.
// Encoding creates a new identifier if none exists for the given URL.
// Decoding extract the identifier from the shortened URL and returns the original URL.

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <assert.h>

// Accepted. 6ms. Beats 12.45% of submissions, ties 58.78% of submissions.
class Solution {
public:
    // Encodes a URL to a shortened URL.
    std::string encode(const std::string& long_url) {
        auto found = m_url_to_id.find(long_url);
        if (found != m_url_to_id.end()) {
            return build_tinyurl(found->second);
        }

        std::string tiny_url = build_tinyurl(m_id);
        m_id_to_url[m_id] = long_url;
        m_url_to_id[long_url] = m_id;
        next_id();
        return tiny_url;
    }

    // Decodes a shortened URL to its original URL.
    std::string decode(const std::string& short_url) {
        size_t index = short_url.rfind('/');
        std::string id = short_url.substr(index+1, std::string::npos);
        return m_id_to_url[id];
    }

private:
    std::string m_id = "aaaaaa";
    std::unordered_map<std::string, std::string> m_id_to_url;   // identifiers -> long URL
    std::unordered_map<std::string, std::string> m_url_to_id;   // long URL -> identifier
    static const std::string m_base_url;

    inline int next_char(char& c) {
        if (c == 'z') { c = 'a'; return 1; }
        ++c;
        return 0;
    }

    inline void next_id() {
        int carry = 1;
        int index = 5;
        while (index >= 0 && carry > 0) {
            carry = next_char(m_id[index--]);
        }
    }

    inline std::string build_tinyurl(const std::string& id) {
        std::string url = m_base_url;
        url.append(id);
        return url;
    }
};
const std::string Solution::m_base_url = "http://www.tinyurl.com/";

void test_tiny_url() {
    Solution soln;
    const int num_urls = 5;
    std::string urls[num_urls] = {
        "http://www.cnn.com", "http://bbc.co.uk", "http://guardian.co.uk", "http://www.nytimes.com", "http://huffpost.ca"
    };

    std::vector<std::string> tiny_urls;
    std::unordered_set<std::string> unique_tiny_urls;

    for (int i = 0; i < num_urls; ++i) {
        auto tiny_url = soln.encode(urls[i]);
        assert(unique_tiny_urls.count(tiny_url) == 0);
        unique_tiny_urls.insert(tiny_url);
        tiny_urls.emplace_back(tiny_url);
    }

    for (int i = 0; i < num_urls; ++i) {
        assert(soln.decode(tiny_urls[i]) == urls[i]);
    }
}

int main(int argc, char** argv) {
    test_tiny_url();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}