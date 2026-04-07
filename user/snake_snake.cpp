#include <stdint.h>
#include "snake_map.h"
#include "snake_snake.h"


static constexpr int8_t dir_dx[] = { 0, 1, 0, -1};
static constexpr int8_t dir_dy[] = {-1, 0, 1,  0};

void Snake::try_set_dir(const Dir new_dir) {
    if (((new_dir ^ dir) & 1) == 0)
        return;
    dir = new_dir;
}

Point Snake::next_head() const {
    Point h = body[head_idx];
    return Point(
        (h.x + MAP_W + dir_dx[dir]) % MAP_W,
        (h.y + MAP_H + dir_dy[dir]) % MAP_H
    );
}

bool Snake::move(bool on_apple) {
    Point new_head = next_head();
    head_idx = (head_idx + 1) % MAX_SNAKE;
    body[head_idx] = new_head;

    if (on_apple) {
        gs_push(move_count + snake_len + gs_size());
    }

    bool with_grow = false;
    if (!gs_empty() && move_count == gs_front()) {
        with_grow = true;
        gs_pop();
    }

    move_count++;

    if (with_grow) {
        snake_len++;
    } else {
        tail_idx = (tail_idx + 1) % MAX_SNAKE;
    }

    return with_grow;
}

Point Snake::head() const { return body[head_idx]; }
Point Snake::tail() const { return body[tail_idx]; }

Snake::Snake(uint16_t x, uint16_t y)
    : dir(LEFT), head_idx(0), tail_idx(0),
      snake_len(1), move_count(0), gs_head(0), gs_tail(0)
{
    body[0] = {x, y};
}