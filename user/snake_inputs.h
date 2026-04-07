#pragma once
#include <cstdint>

enum Scancode : uint8_t {
    SC_ESC   = 0x01,
    SC_1     = 0x02,
    SC_W     = 0x11,
    SC_A     = 0x1E,
    SC_S     = 0x1F,
    SC_D     = 0x20,
    SC_P     = 0x19,
    SC_ENTER = 0x1C,
    SC_SPACE = 0x39,
};

void sync_input();
int is_pressed(uint8_t key);
int is_held(uint8_t key);
