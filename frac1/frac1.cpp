/*
TASK: frac1
USER: dionyzi1
LANG: C++
*/

#include <cstdio>

using namespace std;

int main() {
    FILE* in = fopen("frac1.in", "r"),
        * out = fopen("frac1.out", "w");
    int N, a = 0, b = 1, c = 1, d, p, q, k;

    fscanf(in, "%i", &N);
    d = N;

    fprintf(out, "0/1\n");
    fprintf(out, "%i/%i\n", c, d);

    while (!(c == 1 && d == 1)) {
        k = (N + b) / d;
        p = k * c - a;
        q = k * d - b;
        fprintf(out, "%i/%i\n", p, q);
        a = c;
        b = d;
        c = p;
        d = q;
    }

    return 0;
}
