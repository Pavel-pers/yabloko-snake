#pragma once

uintptr_t* get_cur_pgdir(void);
void run_elf(const char* name);
_Noreturn void killproc();
