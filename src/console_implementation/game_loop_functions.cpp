#include "main_header.hpp"


bool gameloop()
{
    std::shared_ptr<Tplayer> main_player = std::make_shared<Tplayer>("main_player", std::make_shared<player_drawing_module>());
    main_player -> change_current_position(Tposition(20,20));
    WINDOW* gameplay_window;
    WINDOW* scoreboard_window;

    scoreboard_window = window_scoreboard_output();
    gameplay_window = window_gameplay_output();

    while(true)
    {
        input_processing(main_player);  // --->  get_input thread as input_processing part of the loop?
        //update(); --> one step forward all movement mechanics
        //render(); --> rendering with delta time
    }

    return false;
}


bool input_processing(const std::shared_ptr<Ientity>& player)
{
    int input;
    bool exit = false;

    //while(!exit)
    //{
        input = getchar();
        switch(input)
        {
            case 'W':
                player -> move(Ientity::Movement::Up);
                break;
            case 'w':
                player -> move(Ientity::Movement::Up);
                break;

            case 'S':
                player -> move(Ientity::Movement::Down);
                break;
            case 's':
                player -> move(Ientity::Movement::Down);
                break;

            case 'A':
                player -> move(Ientity::Movement::Left);
                break;
            case 'a':
                player -> move(Ientity::Movement::Left);
                break;

            case 'D':
                player -> move(Ientity::Movement::Right);
                break;
            case 'd':
                player -> move(Ientity::Movement::Right);
                break;

            case char(27):
                exit = true;
                break;
            default:
                break;
        }
    //}

    return true;
}

WINDOW* window_gameplay_output()
{
    WINDOW* new_window;

    const unsigned int height = 40;
    const unsigned int width = 140;
    const unsigned int startX = 1;
    const unsigned int startY = 1;

    new_window = newwin(height, width, startY, startX);
    wborder(new_window, '|', '|', '-', '-', '+', '+', '+' , '+');
    wrefresh(new_window);

    return new_window;
}

WINDOW* window_scoreboard_output()
{
    WINDOW* new_window;

    const unsigned int height = 40;
    const unsigned int width = 20;
    const unsigned int startX = 142;
    const unsigned int startY = 1;

    new_window = newwin(height, width, startY, startX);
    wborder(new_window, '|', '|', '-', '-', '+', '+', '+' , '+');
    wrefresh(new_window);

    return new_window;
}