#pragma once
#include <cstdint>

namespace Game {
    void init(int apple_count);
    bool update();
    void render();
    int  final_score();
}