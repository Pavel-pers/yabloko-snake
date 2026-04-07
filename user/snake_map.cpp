#include "snake_map.h"
#include "snake_random.h"

bool spawn_bonus() {
    int y_seed = rand() % MAP_H;
    int x_seed = rand() % MAP_W;

    for (int yd = 0; yd < MAP_H; yd++) {
        for (int xd = 0; xd < MAP_W; xd++) {
            int new_y = (yd + y_seed) % MAP_H;
            int new_x = (xd + x_seed) % MAP_W;
            if (map[new_y][new_x] != CELL_BONUS) {
                map[new_y][new_x] = CELL_BONUS;
                return true;
            }
        }
    }
    return false;
}

void generate_map() {
    for (int i = 0; i < BONUS_N; i++) spawn_bonus();
}
