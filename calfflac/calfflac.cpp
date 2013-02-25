/*
USER: dionyzi1
TASK: calfflac
LANG: C++
*/

#include <cstdio>
#include <cassert>
#include <cctype>
#include <algorithm>

using namespace std;

struct Substring {
    int begin;
    int length;
};

Substring largestPalindrome(char* haystack, int n) {
    int maxLength = 0, maxBegin = 0, length;
    bool even = false;

    for (int center = 0; center < n; ++center) {
        // odd
        for (length = 1; length + center < n && center - length >= 0; ++length) {
            if (haystack[center - length] != haystack[center + length]) {
                if (2 * (length - 1) + 1 > maxLength) {
                    maxLength = 2 * (length - 1) + 1;
                    maxBegin = center - (length - 1);
                    even = false;
                }
                break;
            }
        }
        if (2 * (length - 1) + 1 > maxLength) {
            maxLength = 2 * (length - 1) + 1;
            maxBegin = center - (length - 1);
            even = false;
        }
        // even, after center
        for (length = 1; length + center < n && center - length >= -1; ++length) {
            if (haystack[center - length + 1] != haystack[center + length]) {
                if (2 * (length - 1) > maxLength) {
                    maxLength = 2 * (length - 1);
                    maxBegin = center - (length - 1) + 1;
                    even = true;
                }
                break;
            }
        }
        if (2 * (length - 1) > maxLength) {
            maxLength = 2 * (length - 1);
            maxBegin = center - (length - 1) + 1;
            even = true;
        }
    }
    if (even) {
        return (Substring){maxBegin, maxLength};
    }
    return (Substring){maxBegin, maxLength};
}

int main() {
    FILE* in = fopen("calfflac.in", "r"),
        * out = fopen("calfflac.out", "w");
    char input[20000];
    char clean[20000];
    int c, n = 0, i = 0, j = 0;

    while ((c = fgetc(in)) != EOF) {
        input[n++] = c;
        if (isalpha(c)) {
            clean[i++] = tolower(c);
        }
    }
    Substring location = largestPalindrome(clean, i);
    fprintf(out, "%i\n", location.length);

    for (j = 0, i = 0; i < n; ++i) {
        if (location.begin <= j && j < location.begin + location.length) {
            if (location.begin != j || isalpha(input[i])) {
                fprintf(out, "%c", input[i]);
            }
        }
        if (isalpha(input[i])) {
            ++j;
        }
    }
    fprintf(out, "\n");

    return 0;
}
