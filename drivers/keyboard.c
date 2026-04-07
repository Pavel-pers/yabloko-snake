#include "keyboard.h"
#include "cpu/isr.h"
#include "cpu/memlayout.h"
#include "console.h"
#include "port.h"
#include "kernel/mem.h"
#include "syscall.h"

#define KEYBORD_RING_SIZE 64

static const char sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
    'u', 'i', 'o', 'p', '[', ']', '\n', '?', 'a', 's', 'd', 'f', 'g',
    'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' ',
};

enum { kbd_buf_capacity = PGSIZE };

static struct KeyboardEvent kbd_ring[KEYBORD_RING_SIZE];
static volatile int head = 0;
static volatile int tail = 0;

static void interrupt_handler(registers_t *r) {
    uint8_t scancode = port_byte_in(0x60);

    int next = (head + 1) & (KEYBORD_RING_SIZE - 1);
    if (next != tail) {
        kbd_ring[head].scancode = scancode & 0x7F;
        kbd_ring[head].flag = (scancode >> 7) & 1;
        head = next;
    }

    // legacy
    if (scancode < sizeof(sc_ascii)) {
        char c = sc_ascii[scancode];
        if (kbd_buf_size < kbd_buf_capacity) {
            kbd_buf[kbd_buf_size++] = c;
        }
        char string[] = {c, '\0'};
        printk(string);
    }
}

int kbd_read_events(struct KeyboardEvent *buf, int max) {
    int count = 0;
    while (tail != head && count < max) {
        buf[count++] = kbd_ring[tail];
        tail = (tail + 1) & (KEYBORD_RING_SIZE - 1);
    }
    return count;
}

char* kbd_buf;
unsigned kbd_buf_size;

void init_keyboard() {
    kbd_buf = kalloc();

    register_interrupt_handler(IRQ1, interrupt_handler);
}
