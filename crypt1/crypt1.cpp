/*
USER: dionyzi1
TASK: crypt1
LANG: C++
*/
#include <cstdio>
#include <set>
#include <cstring>

using namespace std;

set< int > digits;

bool valid(int input, int num_digits) {
    int len;
    char str[10];

    sprintf(str, "%i", input);
    len = strlen(str);
    if (len != num_digits) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (digits.find(str[i] - '0') == digits.end()) {
            return false;
        }
    }
    return true;
}

bool mul_valid(int a, int b) {
    return valid(a, 3)
        && valid(b, 2)
        && valid(a * (b % 10), 3)
        && valid(a * (b / 10), 3)
        && valid(a * b, 4);
}

int main() {
    FILE* in = fopen("crypt1.in", "r"),
        * out = fopen("crypt1.out", "w");
    int c = 0, i, j, n, digit;

    fscanf(in, "%i", &n);
    for (i = 0; i < n; ++i) {
        fscanf(in, "%i", &digit);
        digits.insert(digit);
    }

    for (i = 100; i < 1000; ++i) {
        for (j = 10; j < 100; ++j) {
            c += mul_valid(i, j);
        }
    }
    fprintf(out, "%i\n", c);

    return 0;
}
