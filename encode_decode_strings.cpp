// Leetcode: https://leetcode.com/problems/encode-and-decode-strings/description/
// Design an algorithm to encode a list of strings to a string. The encoded string is then sent 
// over the network and is decoded back to the original list of strings.


// Approach: Serialize the input strings in the following format
// <length> <string_bytes> <length> <string_bytes> ...
// where <length> is sizeof(unsigned) bytes
// and <string_bytes> are the raw bytes of the string
// This is not portable across endian-ness or word-size boundaries

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using Strings = std::vector<std::string>;

// Accepted. 48ms. Beats 81.23% of submissions, ties 0.32% of submissions.
class Codec {
public:
    std::string encode(const Strings& strs) {
        std::string result;
        int total_size = 0;
        for (auto& s : strs) { total_size += s.size(); }
        result.reserve(total_size);
        for (auto& s : strs) {
            unsigned size(s.size());
            char* len = reinterpret_cast<char*>(&size);
            result.append(len, sizeof(unsigned));
            result.append(s);
            while (result.size() % sizeof(unsigned)) { result.append (1, '\0'); } // word-align

        }
        std::cout << "Encode: " << result << std::endl;
        std::cout << "Encode Size: " << result.size() << std::endl;
        return result;
    }

    Strings decode(std::string s) {
        Strings result;
        int i = 0;
        while (i < s.size()) {
            unsigned* size = reinterpret_cast<unsigned*>(&s[i]);
            i += sizeof(unsigned);
            result.emplace_back(&s[i], *size);
            i += *size;
            while (i % sizeof(unsigned)) { ++i; } // word-align

        }
        return result;
    }
};

bool test_encode_decode(Strings strs) {
    Codec c;
    return c.decode(c.encode(strs)) == strs;
}

void test_encode_decode() {
    assert(test_encode_decode({}));
    assert(test_encode_decode({""}));
    assert(test_encode_decode({"Hello"}));
    assert(test_encode_decode({"Hello", "World"}));
    assert(test_encode_decode({"Hello", "World", "Again"}));
    assert(test_encode_decode({"Hello", "World", "Again", ""}));
    assert(test_encode_decode({"Hello", "World", "Again", "\0"}));
}

int main(int argc, char** argv) {
    test_encode_decode();
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
