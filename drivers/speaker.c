#include <stdint.h>
#include <assert.h>
#include "port.h"
#include "speaker.h"

const uint32_t PIT_FREQ = 1193182;

void setup_speaker(uint32_t freq) {
    assert(freq > 0);

    uint32_t delta_freq = PIT_FREQ / freq;

    port_byte_out(0x43, 0xB6); // setup pit for speaker lo-hi communication
    port_byte_out(0x42, (uint8_t)(delta_freq & ((1 << 8) - 1))); // lo token
    port_byte_out(0x42, (uint8_t)((delta_freq >> 8) & ((1 << 8) - 1))); // hi token

    uint8_t prev_status = port_byte_in(0x61);
    port_byte_out(0x61, prev_status | 3); // turn on speaker and reading
}

void off_speaker() {
    uint8_t prev_status = port_byte_in(0x61);
    port_byte_out(0x61, prev_status & ~3);
}
