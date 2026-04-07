#include <stdint.h>
#include "../syscall.h"

static uint8_t key_pressed[256];
static uint8_t key_state[256];

void sync_input() {
    for (int i = 0; i < 256; i++) {
        key_pressed[i] = 0;
    }

    struct KeyboardEvent events[64];
    int n = syscall2(SYS_getkeys, (uint64_t)events, 64);

    for (int i = 0; i < n; i++) {
        uint8_t ch = events[i].scancode;
        uint8_t released = events[i].flag & 1;

        if (released) {
            key_state[ch] = 0;
        }
        else {
            if (key_state[ch] == 0) {
                key_pressed[ch] = 1;
            }
            key_state[ch] = 1;
        }
    }
}

int is_pressed(uint8_t key) {
    return key_pressed[key];
}

int is_held(uint8_t key) {
    return key_state[key];
}
