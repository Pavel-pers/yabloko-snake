#pragma once
#include <cstdint>

constexpr uint16_t MAP_W = 32;
constexpr uint16_t MAP_H = 20;
constexpr uint16_t BONUS_N = 5;

enum Cell
{
    CELL_EMPTY = 0,
    CELL_WALL = 1,
    CELL_BONUS = 2,
    CELL_SNAKE = 3
};

struct Point
{
    uint16_t x;
    uint16_t y;

    Point(uint16_t x, uint16_t y) : x(x), y(y) {}
    Point() = default;
};

uint8_t map[MAP_H][MAP_W];

void generate_map();
bool spawn_bonus();
