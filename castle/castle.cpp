/*
TASK: castle
USER: dionyzi1
LANG: C++
*/

#include <cstdio>
#include <queue>

using namespace std;

enum Direction {
    WEST = 1,
    NORTH = 2,
    EAST = 4,
    SOUTH = 8
};

struct Module {
    int walls;
    int room;
    bool visited;
};

const int MAX_N = 50;

Module castle[MAX_N][MAX_N];
int room_sizes[MAX_N * MAX_N];

inline char direction_to_char(Direction d) {
    if (d == NORTH) {
        return 'N';
    }
    return 'E';
}

inline int differential_to_direction(int dx, int dy) {
    switch (dx) {
        case -1:
            return WEST;
        case 1:
            return EAST;
    }
    switch (dy) {
        case -1:
            return NORTH;
    }
    return SOUTH;
}

int BFS(int x, int y, int room) {
    queue< pair< int, int > > q;
    pair< int, int > r;
    int room_size = 0;

    q.push(make_pair(x, y));
    while (!q.empty()) {
        r = q.front();
        q.pop();
        int x = r.first, y = r.second;
        if (castle[y][x].visited) {
            continue;
        }
        ++room_size;

        castle[y][x].visited = true;
        castle[y][x].room = room;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if ((dx == 0) != (dy == 0)) {
                    if (!(castle[y][x].walls & differential_to_direction(dx, dy))) {
                        if (!castle[y + dy][x + dx].visited) {
                            // map boundaries are explicit walls
                            q.push(make_pair(x + dx, y + dy));
                        }
                    }
                }
            }
        }
    }

    return room_size;
}

int main() {
    FILE* in = fopen("castle.in", "r"),
        * out = fopen("castle.out", "w");
    int N, M, room_id = 0, largest_room_size = 0, largest_creatable_size = 0;
    pair< int, int > demolishion_module;
    Direction demolishion_direction = EAST;

    fscanf(in, "%i %i", &M, &N);

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            fscanf(in, "%i", &castle[y][x].walls);
        }
    }

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            if (!castle[y][x].visited) {
                room_sizes[room_id] = BFS(x, y, room_id);
                largest_room_size = max(largest_room_size, room_sizes[room_id]);
                ++room_id;
            }
        }
    }

    for (int x = M - 1; x >= 0; --x) {
        for (int y = 0; y < N; ++y) {
            int new_room_size;

            if (x != M - 1) {
                // EAST
                if (castle[y][x].room != castle[y][x + 1].room) {
                    new_room_size = room_sizes[castle[y][x].room] + room_sizes[castle[y][x + 1].room];
                    if (new_room_size >= largest_creatable_size) {
                        largest_creatable_size = new_room_size;
                        demolishion_module = make_pair(x, y);
                        demolishion_direction = EAST;
                    }
                }
            }
            if (y != 0) {
                // NORTH
                if (castle[y][x].room != castle[y - 1][x].room) {
                    new_room_size = room_sizes[castle[y][x].room] + room_sizes[castle[y - 1][x].room];
                    if (new_room_size >= largest_creatable_size) {
                        largest_creatable_size = new_room_size;
                        demolishion_module = make_pair(x, y);
                        demolishion_direction = NORTH;
                    }
                }
            }
        }
    }

    fprintf(out, "%i\n", room_id);
    fprintf(out, "%i\n", largest_room_size);
    fprintf(out, "%i\n", largest_creatable_size);
    fprintf(out, "%i %i %c\n", demolishion_module.second + 1, demolishion_module.first + 1, direction_to_char(demolishion_direction));

    return 0;
}
