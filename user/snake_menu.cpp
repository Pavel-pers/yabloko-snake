#include "snake_menu.h"
#include "snake_render.h"
#include "snake_inputs.h"
#include "snake_sounds.h"

namespace Menu
{
    static int selection = 0;
    static int apples = 5;

    void init() {
        selection = 0;
    }

    bool update() {
        if (is_pressed(SC_W) || is_pressed(SC_S)) {
            selection = 1 - selection;
            sfx_click();
        }
        if (selection == 1) {
            if (is_pressed(SC_D) && apples < 20) {
                apples++;
                sfx_click();
            }
            if (is_pressed(SC_A) && apples > 1) {
                apples--;
                sfx_click();
            }
        }

        bool start = is_pressed(SC_ENTER) && selection == 0;
        if (start) {
            sfx_start();
        }
    }

    void render() {
        clear_screen(0);
        draw_string(110, 30, "SNAKE", 15);

        uint8_t c0 = selection == 0 ? 14 : 7;
        uint8_t c1 = selection == 1 ? 14 : 7;
        draw_string(100, 80, "START", c0);
        draw_string(100, 100, "APPLES:", c1);
        draw_number(160, 100, apples, c1);
    }

    int apple_count() {
        return apples;
    }
}

namespace GameOver {
    static int final_score = 0;
    static bool pressed = false;

    void init(int score) {
        final_score = score;
        pressed = false;
    }

    bool update() {
        return is_pressed(SC_ENTER);
    }

    void render() {
        fill_rectangle(60, 60, 200, 80, 0);
        draw_string(100, 75, "GAME OVER", 12);
        draw_string(85, 95, "SCORE:", 15);
        draw_number(140, 95, final_score, 14);
        draw_string(70, 120, "ENTER:RESTART", 7);
    }
}
