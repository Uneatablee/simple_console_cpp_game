#include "main_header.hpp"

bool game_over = false;
bool alive_input = false;

int main()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();

    gameloop(); //--> gameloop with gameplaywindow and player (score window addition later)

    //getting Idrawable from libs to console implementation
    //getting Idrawable to work for player and input->move possibility in a game loop
    //wall collision detecting

    //IDEAS:
    //scoreboard fps showcase

    endwin();
}
