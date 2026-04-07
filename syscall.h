#pragma once
#include <stdint.h>

enum {
	T_SYSCALL = 0x84,
	SYS_exit = 0,
	SYS_greet = 1,
	SYS_putc = 2,
	SYS_puts = 3,
	SYS_getkeys = 4,
	SYS_time = 5,
	SYS_sleep = 6,
	SYS_sound = 7,
	SYS_setmode13 = 8,
	SYS_setmode3 = 9
};

struct KeyboardEvent {
	uint8_t scancode;
	uint8_t flag;
};

int syscall(int call, int arg);
int syscall2(int call, int arg1, int arg2);
int syscall3(int call, int arg1, int arg2, int arg3);
