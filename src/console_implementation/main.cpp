#include "main_header.hpp"

bool game_over = false;
bool alive_input = false;

int main()
{
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();
    std::shared_ptr<Idrawable> player_drawer = std::make_shared<player_drawing_module>();

    std::shared_ptr<Tplayer> main_player = std::make_shared<Tplayer>("main_player", player_drawer);
    main_player -> change_current_position(Tposition(20,20));

    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();

    WINDOW* gameplay_window;
    gameplay_window = window_game_output();
    std::thread get_input(input_processing, main_player);

    //gameloop(); --> gameloop with gameplaywindow and player (score window addition later)
    //getting Idrawable from libs to console implementation
    //getting Idrawable to work for player and input->move possibility in a game loop
    //wall collision detecting
    //tickrate refreshing with delta time

    //IDEAS:
    //scoreboard fps showcase

    get_input.join();

    endwin();
}
