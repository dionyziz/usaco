/*
TASK: sort3
USER: dionyzi1
LANG: C++
*/

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 1024;

int counts[4];
int in_place[4][4];

int main() {
    FILE* in = fopen("sort3.in", "r"),
        * out = fopen("sort3.out", "w");
    int N, A[MAX_N], exchanges = 0, m;

    fscanf(in, "%i", &N);
    for (int i = 0; i < N; ++i) {
        fscanf(in, "%i", &A[i]);
        ++counts[A[i]];
    }
    for (int i = 0; i < N; ++i) {
        if (i < counts[1]) {
            ++in_place[A[i]][1];
        }
        else if (i < counts[1] + counts[2]) {
            ++in_place[A[i]][2];
        }
        else {
            ++in_place[A[i]][3];
        }
    }
    m = min(in_place[1][2], in_place[2][1]);
    exchanges += m;
    in_place[1][2] -= m;
    in_place[2][1] -= m;

    m = min(in_place[1][3], in_place[3][1]);
    exchanges += m;
    in_place[1][3] -= m;
    in_place[3][1] -= m;

    m = min(in_place[2][3], in_place[3][2]);
    exchanges += m;
    in_place[2][3] -= m;
    in_place[3][2] -= m;

    exchanges += 2 * (in_place[1][2] + in_place[2][1]);

    fprintf(out, "%i\n", exchanges);

    return 0;
}
