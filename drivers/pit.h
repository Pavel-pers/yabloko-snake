#pragma once
#include <stdint.h>

typedef void (*timer_callback)(void);
extern volatile uint32_t pit_ticks;

void init_pit(void);
void add_timer_callback(timer_callback tc);

void msleep(int ms);
