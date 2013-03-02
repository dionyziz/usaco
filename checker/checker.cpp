/*
USER: dionyzi1
TASK: checker
LANG: C++
*/

#include <cstdio>

using namespace std;

const int MAX_N = 20;

int N, A[MAX_N], c = 0, d = 0;
int rowtaken[MAX_N], slashdiagtaken[2 * MAX_N], backslashdiagtaken[2 * MAX_N];

FILE* in,
    * out;

inline int absolute(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
}

int preset[15];

void attempt(int i) {
    if (i == N) {
        if (c < 3) {
            for (int j = 0; j < N; ++j) {
                fprintf(out, "%i", A[j] + 1);
                if (j != N - 1) {
                    fprintf(out, " ");
                }
            }
            fprintf(out, "\n");
        }
        ++c;
        return;
    }
    else if (i == N - 1) {
        for (int j = 0; j < N; ++j) {
            preset[j] = 0;
        }
        for (int j = 0; j < N; ++j) {
            preset[A[j]] = 1;
        }
        for (int j = 0; j < N; ++j) {
            if (preset[j] == 0) {
                A[i] = j;
            }
        }
    }

    for (int j = 0; j < N; ++j) {
        if (i == 0 && N > 7) {
            // symmetry
            if (2 * j + 1 == N) {
                // odd case, middle
                d = c;
            }
            if (2 * j == N) {
                // even case, past middle
                d = c;
            }
            if (2 * j >= N) {
                // both cases
                c += d;
                return;
            }
        }
        if (!rowtaken[j]
        && !slashdiagtaken[j + i]
        && !backslashdiagtaken[MAX_N + j - i]) {
            rowtaken[j] = 1;
            slashdiagtaken[j + i] = 1;
            backslashdiagtaken[MAX_N + j - i] = 1;
            A[i] = j;
            attempt(i + 1);
            rowtaken[j] = 0;
            slashdiagtaken[j + i] = 0;
            backslashdiagtaken[MAX_N + j - i] = 0;
        }
    }
}

int main() {
    in = fopen("checker.in", "r");
    out = fopen("checker.out", "w");

    fscanf(in, "%i", &N);

    attempt(0);

    fprintf(out, "%i\n", c);

    return 0;
}
