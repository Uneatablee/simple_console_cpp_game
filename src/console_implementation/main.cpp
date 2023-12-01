#include "main_header.hpp"

bool game_over = false;
bool alive_input = false;

int main()
{
    WINDOW* standard_screen = initscr();
    cbreak();
    keypad(standard_screen, true);
    noecho();

    gameloop(); //--> gameloop with gameplaywindow and player (score window addition later)

    //wall collision detecting

    //IDEAS:
    //scoreboard fps showcase

    endwin();
    standard_screen = nullptr;
}
