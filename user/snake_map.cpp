#include "snake_map.h"
#include "snake_random.h"

uint8_t map[MAP_H][MAP_W];

bool spawn_bonus() {
    int y_seed = rand() % MAP_H;
    int x_seed = rand() % MAP_W;

    for (int yd = 0; yd < MAP_H; yd++) {
        for (int xd = 0; xd < MAP_W; xd++) {
            int new_y = (yd + y_seed) % MAP_H;
            int new_x = (xd + x_seed) % MAP_W;
            if (map[new_y][new_x] == CELL_EMPTY) {
                map[new_y][new_x] = CELL_BONUS;
                return true;
            }
        }
    }
    return false;
}

void generate_map() {
    for (int y = 0; y < MAP_H; y++)
        for (int x = 0; x < MAP_W; x++)
            map[y][x] = CELL_EMPTY;
}
