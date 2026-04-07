#pragma once
#include <cstdint>

namespace Menu {
    void init();
    bool update();
    void render();   
    int  apple_count();
}

namespace GameOver {
    void init(int score);
    bool update();
    void render();
}