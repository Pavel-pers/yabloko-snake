#include <stdint.h>

#include "../syscall.h"

static void make_sound(uint32_t freq, uint32_t duration) {
    syscall(SYS_sound, freq);
    syscall(SYS_sleep, (uint32_t)duration);
    syscall(SYS_sound, 0);
}

void sfx_happy() {
    make_sound(880, 40);
    make_sound(1175, 40);
}

void sfx_sad() {
    make_sound(440, 120);
    make_sound(330, 120);
    make_sound(220, 250);
}

void sfx_select() {
    make_sound(660, 30);
}

void sfx_click() {
    syscall(SYS_sound, 1000);
    syscall(SYS_sleep, 20);
    syscall(SYS_sound, 0);
}

void sfx_start() {
    syscall(SYS_sound, 523);   
    syscall(SYS_sleep, 60);
    syscall(SYS_sound, 659);   
    syscall(SYS_sleep, 60);
    syscall(SYS_sound, 784);   
    syscall(SYS_sleep, 80);
    syscall(SYS_sound, 0);
}
