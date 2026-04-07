#pragma once
#include <cstdint>

uint32_t rand() {
    static constexpr uint32_t BASE = 31;
    static constexpr uint32_t K = 69696;
    static uint32_t X_ = 1;
    X_ = (X_ + BASE) * K;
    return X_;
}