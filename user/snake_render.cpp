#include <stdint.h>
#include "snake_render.h"
#include "../syscall.h"

static uint8_t* vb;

void render_init() {
    syscall(SYS_setmode13, VB_ADDR);
    vb = (uint8_t*)VB_ADDR;
}

void render_shutdown() {
    syscall(SYS_setmode3, 0);
}

void set_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < (int)SCREEN_W && y >= 0 && y < (int)SCREEN_H)
        vb[y * SCREEN_W + x] = color;
}

void fill_rectangle(int x, int y, int w, int h, uint8_t color) {
    for (int yi = y; yi < y + h; yi++)
        for (int xi = x; xi < x + w; xi++)
            set_pixel(xi, yi, color);
}

void clear_screen(uint8_t color) {
    for (uint32_t i = 0; i < SCREEN_W * SCREEN_H; i++)
        vb[i] = color;
}

#define FONT_W 5
#define FONT_H 7

static const uint8_t font_chars[] = " 0123456789:ACEGKLMNOPRSTV W";
static const uint8_t font_bitmaps[][FONT_H] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // ' '
    {0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70}, // '0'
    {0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70}, // '1'
    {0x70, 0x88, 0x08, 0x30, 0x40, 0x80, 0xF8}, // '2'
    {0x70, 0x88, 0x08, 0x30, 0x08, 0x88, 0x70}, // '3'
    {0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10}, // '4'
    {0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70}, // '5'
    {0x30, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70}, // '6'
    {0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40}, // '7'
    {0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70}, // '8'
    {0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60}, // '9'
    {0x00, 0x20, 0x20, 0x00, 0x20, 0x20, 0x00}, // ':'
    {0x40, 0xA0, 0xA0, 0xE0, 0xA0, 0xA0, 0x00}, // 'A'
    {0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70}, // 'C'
    {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8}, // 'E'
    {0x70, 0x88, 0x80, 0xB8, 0x88, 0x88, 0x70}, // 'G'
    {0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88}, // 'K'
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8}, // 'L'
    {0x88, 0xD8, 0xA8, 0x88, 0x88, 0x88, 0x88}, // 'M'
    {0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x88}, // 'N'
    {0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70}, // 'O'
    {0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80}, // 'P'
    {0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88}, // 'R'
    {0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70}, // 'S'
    {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20}, // 'T'
    {0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20}, // 'V'
    {0x88, 0x88, 0x88, 0xA8, 0xA8, 0xD8, 0x88}, // 'W'
};

static const uint8_t* get_glyph(char ch) {
    for (int i = 0; font_chars[i]; i++)
        if (font_chars[i] == (uint8_t)ch)
            return font_bitmaps[i];
    return font_bitmaps[0]; // space as fallback
}

void draw_char(int px, int py, char ch, uint8_t color) {
    const uint8_t* g = get_glyph(ch);
    for (int row = 0; row < FONT_H; row++)
        for (int col = 0; col < FONT_W; col++)
            if (g[row] & (0x80 >> col))
                set_pixel(px + col, py + row, color);
}

void draw_string(int px, int py, const char* s, uint8_t color) {
    while (*s) {
        draw_char(px, py, *s, color);
        px += FONT_W + 1;
        s++;
    }
}

void draw_number(int px, int py, int num, uint8_t color) {
    char buf[12];
    int i = 0;
    if (num == 0) {
        buf[i++] = '0';
    }
    else {
        while (num > 0) {
            buf[i++] = '0' + (num % 10);
            num /= 10;
        }
        for (int a = 0, b = i - 1; a < b; a++, b--) {
            char tmp = buf[a];
            buf[a] = buf[b];
            buf[b] = tmp;
        }
    }
    buf[i] = '\0';
    draw_string(px, py, buf, color);
}


void draw_snake_head(int cx, int cy, uint8_t dir) {
    int px = cx * CELL, py = cy * CELL;
    fill_rectangle(px, py, CELL, CELL, 2);
    fill_rectangle(px + 1, py + 1, CELL - 2, CELL - 2, 10);

    int ex1, ey1, ex2, ey2;
    if (dir == 3) {
        ex1 = px + 2; ey1 = py + 2;
        ex2 = px + 2; ey2 = py + 6;
    }
    else if (dir == 1) {
        ex1 = px + 6; ey1 = py + 2;
        ex2 = px + 6; ey2 = py + 6;
    }
    else if (dir == 0) {
        ex1 = px + 2; ey1 = py + 2;
        ex2 = px + 6; ey2 = py + 2;
    }
    else {
        ex1 = px + 2; ey1 = py + 6;
        ex2 = px + 6; ey2 = py + 6;
    }

    fill_rectangle(ex1, ey1, 2, 2, 15);
    fill_rectangle(ex2, ey2, 2, 2, 15);

    int pupil_dx = (dir == 1) - (dir == 3);
    int pupil_dy = (dir == 2) - (dir == 0);
    set_pixel(ex1 + pupil_dx, ey1 + pupil_dy, 0);
    set_pixel(ex2 + pupil_dx, ey2 + pupil_dy, 0);
}

void draw_snake_body(int cx, int cy) {
    int px = cx * CELL, py = cy * CELL;
    fill_rectangle(px, py, CELL, CELL, 2);
    fill_rectangle(px + 1, py + 1, CELL - 2, CELL - 2, 10);
}

void draw_apple(int cx, int cy) {
    int px = cx * CELL, py = cy * CELL;
    int ox = px + 5, oy = py + 5;
    for (int dy = -4; dy <= 4; dy++)
        for (int dx = -4; dx <= 4; dx++)
            if (dx * dx + dy * dy <= 16)
                set_pixel(ox + dx, oy + dy, 12);
    set_pixel(ox - 2, oy - 2, 15);
    set_pixel(ox - 1, oy - 2, 15);
    set_pixel(ox, oy - 5, 2);
    set_pixel(ox + 1, oy - 5, 2);
    set_pixel(ox + 1, oy - 4, 2);
}

void draw_wall(int cx, int cy) {
    int px = cx * CELL, py = cy * CELL;
    fill_rectangle(px, py, CELL, CELL, 7);
    fill_rectangle(px, py + 3, CELL, 1, 8);
    fill_rectangle(px, py + 7, CELL, 1, 8);
    fill_rectangle(px + 4, py, 1, 3, 8);
    fill_rectangle(px + 7, py + 4, 1, 3, 8);
    fill_rectangle(px + 2, py + 8, 1, 2, 8);
}
