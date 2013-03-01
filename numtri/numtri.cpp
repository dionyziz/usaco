/*
USER: dionyzi1
TASK: numtri
LANG: C++
*/
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 1000;

int main() {
    FILE* in = fopen("numtri.in", "r"),
        * out = fopen("numtri.out", "w");
    int N, W[MAX_N][MAX_N], a, m = 0;

    fscanf(in, "%i", &N);
    fscanf(in, "%i", &W[0][0]);
    for (int i = 1; i < N; ++i) {
        fscanf(in, "%i", &a);
        W[i][0] = W[i - 1][0] + a;
        for (int j = 1; j < i; ++j) {
            fscanf(in, "%i", &a);
            W[i][j] = max(W[i - 1][j - 1], W[i - 1][j]) + a;
            m = max(m, W[i][j]);
        }
        fscanf(in, "%i", &a);
        W[i][i] = W[i - 1][i - 1] + a;

        m = max(m, max(W[i][0], W[i][i]));
    }
    fprintf(out, "%i\n", m);

    return 0;
}
