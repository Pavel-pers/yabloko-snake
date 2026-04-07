#include "snake_gameplay.h"
#include "snake_menu.h"
#include "snake_inputs.h"
#include "snake_render.h"
#include "../syscall.h"

enum game_state
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER,
};

static int state = STATE_MENU;

static void game_loop() {
    while (true) {
        sync_input();

        switch (state) {
        case STATE_MENU:
            {
                bool start = Menu::update();
                Menu::render();
                if (start) {
                    state = STATE_PLAYING;
                    Game::init(Menu::apple_count());
                }
                break;
            }
        case STATE_PLAYING:
            {
                bool game_over = Game::update();
                if (game_over) {
                    state = STATE_GAMEOVER;
                    GameOver::init(Game::final_score());
                }
                break;
            }
        case STATE_GAMEOVER:
            {
                bool goto_menu = GameOver::update();
                GameOver::render();
                if (goto_menu) {
                    state = STATE_MENU;
                    Menu::init();
                }
                break;
            }
        }
        syscall(SYS_sleep, 10);
    }
}

extern "C" int main() {
    render_init();
    Menu::init();
    game_loop();
    render_shutdown();
    return 0;
}

