#include "snake_gameplay.h"

#include "snake_map.h"
#include "snake_snake.h"
#include "snake_render.h"
#include "snake_inputs.h"
#include "snake_sounds.h"
#include "../syscall.h"

namespace Game
{
    static Snake snake(0, 0);
    static uint32_t last_update;
    static int score;
    static bool alive;

    void init(int apple_count) {
        generate_map();
        uint16_t sx = MAP_W / 2;
        uint16_t sy = MAP_H / 2;
        snake = Snake(sx, sy);
        map[sy][sx] = CELL_SNAKE;
        score = 0;
        alive = true;
        last_update = (uint32_t)syscall(SYS_time, 0);

        for (int i = 0; i < apple_count; i++)
            spawn_bonus();

        render();
    }

    bool update() {
        if (!alive) return true;

        if (is_pressed(SC_W)) {
            snake.try_set_dir(UP);
        }
        if (is_pressed(SC_D)) {
            snake.try_set_dir(RIGHT);
        }
        if (is_pressed(SC_S)) {
            snake.try_set_dir(DOWN);
        }
        if (is_pressed(SC_A)) {
            snake.try_set_dir(LEFT);
        }

        uint32_t const interval = is_held(SC_SPACE) ? 4 : 14;
        auto const now = (uint32_t)syscall(SYS_time, 0);
        if (now - last_update < interval) {
            return false;
        }

        last_update = now;

        Point old_head = snake.head();
        Point old_tail = snake.tail();
        Point nh = snake.next_head();

        if (map[nh.y][nh.x] == CELL_WALL || map[nh.y][nh.x] == CELL_SNAKE) {
            alive = false;
            sfx_sad();
            return true;
        }

        bool on_apple = (map[nh.y][nh.x] == CELL_BONUS);
        if (on_apple) {
            score++;
            sfx_happy();
        }

        bool grew = snake.move(on_apple);
        map[nh.y][nh.x] = CELL_SNAKE;

        if (!grew) {
            map[old_tail.y][old_tail.x] = CELL_EMPTY;
            fill_rectangle(old_tail.x * CELL, old_tail.y * CELL,
                           CELL, CELL, COLOR_BG);
        }

        if (grew) {
            spawn_bonus();
        }

        draw_snake_body(old_head.x, old_head.y);
        draw_snake_head(nh.x, nh.y, snake.dir);

        if (grew) {
            for (int y = 0; y < MAP_H; y++)
                for (int x = 0; x < MAP_W; x++)
                    if (map[y][x] == CELL_BONUS)
                        draw_apple(x, y);
        }

        fill_rectangle(0, 0, 40, 9, COLOR_BG);
        draw_number(2, 2, score, COLOR_WHITE);

        return false;
    }

    void render() {
        clear_screen(COLOR_BG);
        for (int y = 0; y < MAP_H; y++)
            for (int x = 0; x < MAP_W; x++)
                switch (map[y][x]) {
                case CELL_SNAKE:
                    draw_snake_body(x, y);
                    break;
                case CELL_BONUS:
                    draw_apple(x, y);
                    break;
                case CELL_WALL:
                    draw_wall(x, y);
                    break;
                default:
                    break;
                }
        Point h = snake.head();
        draw_snake_head(h.x, h.y, snake.dir);
        draw_number(2, 2, score, COLOR_WHITE);
    }

    int final_score() {
        return score;
    }
}
