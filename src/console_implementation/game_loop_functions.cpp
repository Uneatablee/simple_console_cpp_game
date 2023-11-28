#include "main_header.hpp"

bool input_processing(const std::shared_ptr<Ientity>& player)
{
    int input;
    bool exit = false;

    while(!exit)
    {
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
    }

    return true;
}

WINDOW* window_game_output()
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