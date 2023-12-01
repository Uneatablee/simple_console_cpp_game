#include "main_header.hpp"


bool gameloop()
{
    WINDOW* gameplay_window;
    WINDOW* scoreboard_window;
    scoreboard_window = initial_window_scoreboard_output();
    gameplay_window = initial_window_gameplay_output();

    std::shared_ptr<drawable_player> main_player = std::make_shared<drawable_player>(gameplay_window, "main_player");
    main_player -> change_current_position(Tposition(20,20));

    while(true)
    {
        input_processing(main_player);  // --->  get_input thread as input_processing part of the loop
        update(gameplay_window, main_player); //--> one step forward all movement mechanics

        //render(); --> rendering with delta time
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return false;

    delwin(gameplay_window);
    delwin(scoreboard_window);
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

WINDOW* initial_window_gameplay_output()
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

WINDOW* initial_window_scoreboard_output()
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

void update(WINDOW* operating_window, std::shared_ptr<drawable_player> main_player)
{
    main_player -> draw(main_player -> get_current_position());
    wmove(operating_window, 0, 0);
    wrefresh(operating_window);
}