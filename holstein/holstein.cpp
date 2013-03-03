/*
TASK: holstein
USER: dionyzi1
LANG: C++
*/

#include <cstdio>

using namespace std;

const int MAX_V = 30, MAX_G = 20;

int main() {
    FILE* in = fopen("holstein.in", "r"),
        * out = fopen("holstein.out", "w");
    int V, G, A[MAX_V], B[MAX_G][MAX_V], C[MAX_V], min_bits = MAX_V,
        best_scoops = 0, bits = 0;

    fscanf(in, "%i", &V);
    for (int i = 0; i < V; ++i) {
        fscanf(in, "%i", &A[i]);
    }
    fscanf(in, "%i", &G);
    for (int i = 0; i < G; ++i) {
        for (int j = 0; j < V; ++j) {
            fscanf(in, "%i", &B[i][j]);
        }
    }
    for (int k = 0; k < (1 << G); ++k) {
        for (int j = 0; j < V; ++j) {
            C[j] = 0;
        }
        bits = 0;
        for (int i = 0; i < G; ++i) {
            if (k & (1 << i)) {
                ++bits;
                for (int j = 0; j < V; ++j) {
                    C[j] += B[i][j];
                }
            }
        }
        bool healthy = true;
        for (int j = 0; j < V; ++j) {
            if (C[j] < A[j]) {
                healthy = false;
            }
        }
        if (healthy) {
            if (bits < min_bits) {
                min_bits = bits;
                best_scoops = k;
            }
        }
    }
    fprintf(out, "%i ", min_bits);
    bits = 0;
    for (int i = 0; i < G; ++i) {
        if (best_scoops & (1 << i)) {
            fprintf(out, "%i", i + 1);
            if (bits != min_bits - 1) {
                fprintf(out, " ");
            }
            ++bits;
        }
    }
    fprintf(out, "\n");

    return 0;
}
