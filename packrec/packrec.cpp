/*
USER: dionyzi1
TASK: packrec
LANG: C++
*/
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int NUM_RECTS = 4;
const int INFINITY = 987654;

struct Segment {
    int s, t;

    bool collides(const Segment& target) {
        return (s <= target.s && s + t > target.s)
            || (target.s <= s && target.s + target.t > s);
    }
};

struct Rect {
    Segment a[2];

    void rotate() {
        swap(a[0].t, a[1].t);
    }
    int area() {
        return a[0].t * a[1].t;
    }
    bool collides(Rect& target) {
        return a[0].collides(target.a[0]) && a[1].collides(target.a[1]);
    }
};

bool operator <(Rect self, Rect target) {
    return make_pair(self.a[0].t, self.a[1].t) < make_pair(target.a[0].t, target.a[1].t);
}

bool next(int follow[NUM_RECTS]) {
    for (int k = NUM_RECTS - 1; k >= 0; --k) {
        if (++follow[k] == k + 1) {
            follow[k] = 0;
            if (k == 0) {
                return false;
            }
            continue; 
        }
        return true;
    }
}

int main() {
    FILE* in = fopen("packrec.in", "r"),
        * out = fopen("packrec.out", "w");
    Rect A[NUM_RECTS], B[NUM_RECTS], min_container;
    set< Rect > solutions;

    min_container.a[0].t = min_container.a[1].t = INFINITY;
    
    for (int i = 0; i < NUM_RECTS; ++i) {
        fscanf(in, "%i %i", &A[i].a[0].t, &A[i].a[1].t);
    }

    for (int j = 0; j < (1 << NUM_RECTS); ++j) { // possible rotations bitmask
        for (int k = 0; k < NUM_RECTS; ++k) { // apply rotations
            B[k] = A[k];
            if ((j >> k) & 1) {
                B[k].rotate();
            }
        }

        do { // go through all possible orderings of rects
            int follow[2][NUM_RECTS]; // for each of the next rects, where will they be positioned?

            // start by attempting to position everything following rect #0, and #0 at the origin
            for (int k = 0; k < NUM_RECTS; ++k) {
                follow[0][k] = follow[1][k] = 0;
            }

            do { // go through all possible positionings in the y-coordinate
                do { // and in the x-coordinate
                    Rect container;

                    container.a[0].t = container.a[1].t = 0;

                    bool collision = false;
                    for (int k = 0; k < NUM_RECTS; ++k) { // apply positioning for k-th rect
                        for (int d = 0; d < 2; ++d) { // apply through both dimensions d = 0 (x), d = 1 (y)
                            if (follow[d][k] == k) { // place it at the origin
                                B[k].a[d].s = 0;
                                continue;
                            }
                            B[k].a[d].s = B[follow[d][k]].a[d].s + B[follow[d][k]].a[d].t; // following another rect
                        }
                        for (int i = 0; i < k; ++i) { // check for collisions with previous rects
                            if (B[i].collides(B[k])) {
                                collision = true;
                                break;
                            }
                        }
                        if (collision) {
                            break;
                        }
                        // calculate container area
                        container.a[0].t = max(container.a[0].t, B[k].a[0].s + B[k].a[0].t);
                        container.a[1].t = max(container.a[1].t, B[k].a[1].s + B[k].a[1].t);
                    }

                    if (!collision) { // a valid arrangement
                        if (container.area() < min_container.area()) {
                            solutions.clear();
                            min_container = container;
                        }
                        if (container.area() == min_container.area()) {
                            solutions.insert(container);
                        }
                    }
                } while (next(follow[0]));
            } while (next(follow[1]));
        } while (next_permutation(B, B + NUM_RECTS));
    }

    fprintf(out, "%i\n", min_container.area());
    for (set< Rect >::iterator it = solutions.begin(); it != solutions.end(); ++it) {
        if (it->a[0].t < it->a[1].t) { // arrangements must be ordered with width < height
            fprintf(out, "%i %i\n", it->a[0].t, it->a[1].t);
        }
    }

    return 0;
}
