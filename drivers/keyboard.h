#pragma once
#include "syscall.h"

void init_keyboard();

int kbd_read_events(struct KeyboardEvent* buf, int max);

extern unsigned kbd_buf_size;
extern char *kbd_buf;
