/*
TASK: ariprog
USER: dionyzi1
LANG: C++
*/

#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

int bisquares[22000];
bool is_bisquare[130000];

int N, M, B = 0;

struct Sequence {
    int start;
    int diff;
};

bool operator <(Sequence a, Sequence b) {
    if (a.diff < b.diff) {
        return true;
    }
    if (a.diff > b.diff) {
        return false;
    }
    return a.start < b.start;
}

void make_bisquares() {
    for (int p = 0; p <= M; ++p) {
        for (int q = 0; q <= M; ++q) {
            if (!is_bisquare[p * p + q * q]) {
                bisquares[B++] = p * p + q * q;
                is_bisquare[p * p + q * q] = true;
            }
        }
    }
}

int main() {
    FILE* in = fopen("ariprog.in", "r"),
        * out = fopen("ariprog.out", "w");
    int count = 0;
    set< Sequence > solutions;

    fscanf(in, "%i %i", &N, &M);
    make_bisquares();

    sort(bisquares, bisquares + B);

    for (int i = 0; i < B; ++i) {
        for (int j = i + 1; j < B; ++j) {
            int a = bisquares[i];
            int c = bisquares[j];
            if ((c - a) % (N - 1) != 0) {
                continue;
            }
            int b = (c - a) / (N - 1);

            int acc = a;
            bool progression = true;

            for (int i = 0; i < N; ++i) {
                if (!is_bisquare[acc]) {
                    progression = false;
                    break;
                }
                acc += b;
            }
            if (progression) {
                solutions.insert((Sequence){ a, b });
                ++count;
            }
        }
    }
    if (count == 0) {
        fprintf(out, "NONE\n");
    }
    for (set< Sequence >::iterator it = solutions.begin(); it != solutions.end(); ++it) {
        fprintf(out, "%i %i\n", it->start, it->diff);
    }

    return 0;
}
