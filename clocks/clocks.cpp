/*
USER: dionyzi1
TASK: clocks
LANG: C++
*/

#include <cstdio>
#include <cmath>

using namespace std;

int clock_state[9], transformed[9];
int moves[9];

const int NUM_MOVES = 9;
const int NUM_CLOCKS = 9;

void init() {
    const string move_codes[] = {
        "ABDE",
        "ABC",
        "BCEF",
        "ADG",
        "BDEFH",
        "CFI",
        "DEGH",
        "GHI",
        "EFHI"
    };

    for (int i = 0; i < NUM_MOVES; ++i) {
        int len = move_codes[i].length();
        for (int j = 0; j < len; ++j) {
            moves[i] |= 1 << (move_codes[i][j] - 'A');
        }
    }
}

void apply(int move) {
    for (int i = 0; i < NUM_CLOCKS; ++i) {
        if ((move >> i) & 1) {
            clock_state[i] = (clock_state[i] + 1) % 4;
        }
    }
}

void unapply() {
    for (int i = 0; i < NUM_CLOCKS; ++i) {
        clock_state[i] = transformed[i];
    }
}

int main() {
    FILE* in = fopen("clocks.in", "r"),
        * out = fopen("clocks.out", "w");
    bool found;
    string s;

    s = "";

    init();
    
    for (int i = 0; i < NUM_CLOCKS; ++i) {
        fscanf(in, "%i", &clock_state[i]);
        clock_state[i] = (clock_state[i] / 3) % 4;
        transformed[i] = clock_state[i];
    }

    for (int i = 0; i < pow(4, NUM_MOVES); ++i) {
        int p = i;
        for (int j = 0; j < NUM_MOVES; ++j) {
            for (int k = 0; k < p % 4; ++k) {
                apply(moves[j]);
            }
            p /= 4;
        }

        found = true;
        for (int j = 0; j < NUM_CLOCKS; ++j) {
            if (clock_state[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            p = i;
            int s = 0, q[NUM_MOVES * 4];
            for (int j = 0; j < NUM_MOVES; ++j) {
                for (int k = 0; k < p % 4; ++k) {
                    q[s++] = j + 1;
                }
                p /= 4;
            }
            for (int j = 0; j < s; ++j) {
                fprintf(out, "%i", q[j]);
                if (j < s - 1) {
                    fprintf(out, " ");
                }
            }
            fprintf(out, "\n");
            break;
        }
        unapply();
    }

    return 0;
}
