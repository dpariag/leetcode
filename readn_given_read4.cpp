// Leetcode: https://leetcode.com/problems/read-n-characters-given-read4/description/
// The API: int read4(char *buf) reads 4 characters at a time from a file and returns the actual number read.
// Use read4() to implement int read(char *buf, int n) that reads n characters from the file.

// Approach: Use a temporary buffer to read up to 4-bytes at a time. Copy only the needed bytes into the dest buffer.
// Carefully track the number of bytes read (e.g., the case that only 2 more bytes are needed but 3 were read).

#include <string.h>
#include <iostream>
#include <assert.h>

// Forward declaration of the read4 API.
int read4(char *buf);

// Accepted. 3ms. Beats 0.86% of submissions, ties 25.22% of submissions.
class Solution {
public:
    int read(char *buf, int n) {
        int total_read = 0;
        char buf4[4];
        char* dest = buf;

        while (n > 0) {
            int num_read = read4(buf4);
            if (num_read == 0) {
                // No more data
                break;
            } else {
                // Copy only the amount of data needed
                num_read = std::min(num_read, n);
                strncpy(dest, buf4, num_read);
                total_read += num_read;
                n -= num_read;
                dest += num_read;
                if (num_read < 4) { break; }
            }
        }
        return total_read;
    }
};

int main(int argc, char** argv) {
    std::cout << argv[0] + 2 << "...OK!" << std::endl;
    return 0;
}
