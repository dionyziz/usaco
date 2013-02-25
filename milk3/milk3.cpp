/*
USER: dionyzi1
TASK: milk3
LANG: C++
*/

#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

struct State {
    int A, B, C;
};

bool operator <(State a, State b) {
    return make_pair(a.A, make_pair(a.B, a.C)) < make_pair(b.A, make_pair(b.B, b.C));
}

int c_A, c_B, c_C;
queue< State > q;
State state;

void visit(int &from, int &to, int c_to) {
    int amount = min(from, c_to - to);
    int old_to = to;
    int old_from = from;
    to += amount;
    from -= amount;
    q.push(state);
    to = old_to;
    from = old_from;
}

int main() {
    set< State > visited;
    int solutions[9000];
    int s = 0;
    FILE* in = fopen("milk3.in", "r"),
        * out = fopen("milk3.out", "w");

    fscanf(in, "%i %i %i", &c_A, &c_B, &c_C);

    state.A = state.B = 0;
    state.C = c_C;

    q.push(state);

    while (!q.empty()) {
        state = q.front();
        q.pop();
        if (visited.find(state) != visited.end()) {
            continue;
        }
        visited.insert(state);
        if (state.A == 0) {
            solutions[s++] = state.C;
        }
        visit(state.A, state.B, c_B);
        visit(state.B, state.A, c_A);
        visit(state.B, state.C, c_C);
        visit(state.C, state.B, c_B);
        visit(state.A, state.C, c_C);
        visit(state.C, state.A, c_A);
    }
    sort(solutions, solutions + s);
    for (int i = 0; i < s; ++i) {
        fprintf(out, "%i", solutions[i]);
        if (i < s - 1) {
            fprintf(out, " ");
        }
    }
    fprintf(out, "\n");

    return 0;
}
