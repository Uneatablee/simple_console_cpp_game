#include "main_header.hpp"

bool game_over = false;
bool alive_input = false;

int main()
{
    const auto standard_screen = std::unique_ptr<WINDOW, void (*)(WINDOW*)>(
        initscr(),
        [](WINDOW*)
        {
            endwin();
        });

    cbreak();
    keypad(standard_screen.get(), TRUE); // https://invisible-island.net/ncurses/ncurses-intro.html
    noecho();

    gameloop(); //--> gameloop with gameplaywindow and player

    //INCLUDE TO STARTING SCREEN -> red curtains so that game uses ansii colours also.
}
