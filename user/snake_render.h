#pragma once
#include <cstdint>

constexpr uint32_t SCREEN_W = 320;
constexpr uint32_t SCREEN_H = 200;
constexpr uint32_t CELL = 10;

enum Color : uint8_t
{
    COLOR_BG = 0,
    COLOR_DGREEN = 2,
    COLOR_RED = 4,
    COLOR_BROWN = 6,
    COLOR_GRAY = 7,
    COLOR_DGRAY = 8,
    COLOR_BGREEN = 10,
    COLOR_BRED = 12,
    COLOR_YELLOW = 14,
    COLOR_WHITE = 15,
};

void render_init();
void render_shutdown();
void set_pixel(int x, int y, uint8_t color);
void fill_rectangle(int x, int y, int w, int h, uint8_t color);
void clear_screen(uint8_t color);
void draw_char(int px, int py, char ch, uint8_t color);
void draw_string(int px, int py, const char* s, uint8_t color);
void draw_number(int px, int py, int num, uint8_t color);
void draw_snake_head(int cx, int cy, uint8_t dir);
void draw_snake_body(int cx, int cy);
void draw_apple(int cx, int cy);
void draw_wall(int cx, int cy);
