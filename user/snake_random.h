#pragma once
#include <stdint.h>

inline uint32_t rand() {
    static uint32_t X_ = 1;
    X_ = (X_ + 31) * 69696;
    return X_;
}