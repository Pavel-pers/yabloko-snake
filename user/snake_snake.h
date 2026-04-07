#pragma once
#include <cstdint>
#include "snake_map.h"

constexpr uint32_t MAX_SNAKE = 32 * 20;

enum Dir
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

struct Snake
{
    uint8_t dir;
    Point body[MAX_SNAKE]{};
    uint32_t head_idx;
    uint32_t tail_idx;
    uint32_t snake_len;
    uint32_t move_count;

    void try_set_dir(const Dir new_dir);
    Point next_head() const;
    bool move(bool on_apple);
    Point head() const;
    Point tail() const;

    uint32_t grow_schedule[MAX_SNAKE];
    uint32_t gs_head = 0;
    uint32_t gs_tail = 0;

    void gs_push(uint32_t val) {
        grow_schedule[gs_head] = val;
        gs_head = (gs_head + 1) % MAX_SNAKE;
    }

    uint32_t gs_front() {
        return grow_schedule[gs_tail];
    }

    void gs_pop() {
        gs_tail = (gs_tail + 1) % MAX_SNAKE;
    }

    bool gs_empty() const {
        return gs_head == gs_tail;
    }

    Snake(uint16_t x, uint16_t y);
};
