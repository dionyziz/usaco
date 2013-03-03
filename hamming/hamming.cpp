/*
TASK: hamming
USER: dionyzi1
LANG: C++
*/

#include <cstdio>
#include <set>
#include <stack>

using namespace std;

const int MAX_B = 8;

int dist[1 << MAX_B][1 << MAX_B];
bool visited[1 << MAX_B];
int N, B, D;

int backtrack[1 << MAX_B];

int DFS(int node, int depth) {
    int i, j;

    if (visited[node]) {
        return -1;
    }
    visited[node] = true;
    for (i = 0; i < (1 << MAX_B); ++i) {
        if (visited[i]) {
            continue;
        }
        bool compatible = true;
        for (j = 0; j < (1 << MAX_B); ++j) {
            if (!visited[j]) {
                continue;
            }
            if (dist[i][j] < D) {
                compatible = false;
                break;
            }
        }
        if (!compatible) {
            continue;
        }
        backtrack[i] = node;
        if (depth + 1 == N) {
            return i;
        }
        int res = DFS(i, depth + 1);
        if (res != -1) {
            return res;
        }
    }
    visited[node] = false;
    return -1;
}

int main() {
    FILE* in = fopen("hamming.in", "r"),
        * out = fopen("hamming.out", "w");
    int i, j, k;
    stack< int > s;

    fscanf(in, "%i %i %i", &N, &B, &D);

    for (i = 0; i < (1 << B); ++i) {
        for (j = 0; j < (1 << B); ++j) {
            dist[i][j] = 0;
            for (k = 0; k < B; ++k) {
                dist[i][j] += ((i >> k) & 1) != ((j >> k) & 1);
            }
        }
    }

    i = DFS(0, 1);
    do {
        s.push(i);
        i = backtrack[i];
    } while (i != 0);
    s.push(0);

    j = 0;
    while (!s.empty()) {
        i = s.top();
        s.pop();
        fprintf(out, "%i", i);
        ++j;
        if (s.size() && j % 10 != 0) {
            fprintf(out, " ");
        }
        if (j % 10 == 0 && s.size()) {
            fprintf(out, "\n");
        }
    }
    fprintf(out, "\n");

    return 0;
}
