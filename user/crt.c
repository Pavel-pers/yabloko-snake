#include "../syscall.h"

int main();

int syscall(int call, int arg) {
    asm("int $0x84": "+a"(call) : "b"(arg));
    return call;
}

int syscall2(int call, int arg1, int arg2) {
    asm("int $0x84": "+a"(call) : "b"(arg1), "c"(arg2));
    return call;
}

int syscall3(int call, int arg1, int arg2, int arg3) {
    asm("int $0x84": "+a"(call) : "b"(arg1), "c"(arg2), "d"(arg3));
    return call;
}


_Noreturn
void _exit(int exit_status) {
    syscall(SYS_exit, exit_status);
    __builtin_unreachable();
}

void _start() {
    _exit(main());
}
