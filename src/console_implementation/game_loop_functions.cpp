#include "main_header.hpp"


bool gameloop()
{
    unsigned int gameplay_window_height;
    unsigned int gameplay_window_width;

    //map setup
    std::string map_name = "level_1_map.txt";
    std::string map_layout = map_converter(map_name, &gameplay_window_height, &gameplay_window_width); //converting file and getting single string, height and width of gamepolay window

    //starting level setup
    std::shared_ptr<Ilevel> starting_level = std::make_shared<Tlevel>(map_layout, gameplay_window_height, gameplay_window_width);
    starting_level -> set_starting_position(Tposition(20,20));

    //windows setup
    WINDOW* gameplay_window;
    WINDOW* scoreboard_window;
    scoreboard_window = initial_window_scoreboard_output();
    gameplay_window = initial_window_gameplay_output(starting_level,gameplay_window_height, gameplay_window_width);

    //player setup
    std::shared_ptr<drawable_player> main_player = std::make_shared<drawable_player>(gameplay_window, "main_player");
    main_player -> assign_level(starting_level);

    //GAME LOOP <------------------->
    std::thread input_process(input_processing, main_player); //--> extracted from game loop ---> its not blocking game updating

    while(true)
    {
        update(gameplay_window, main_player); //--> one step forward all movement mechanics

        //render(); --> rendering with delta time ---> colours and Ansi codes generator
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    //clearing
    input_process.join();
    delwin(gameplay_window);
    delwin(scoreboard_window);

    return false;
}


bool input_processing(const std::shared_ptr<Ientity>& player)
{
    int input;
    bool exit = false;
    bool only_side_movement_allowed = false;
    unsigned int step_multiplier = 4;    //left and right step length

    while(!exit)
    {
        step_multiplier = 4;
        only_side_movement_allowed = false;
        input = getchar();

        if(player -> get_current_state() == Ientity::Air_state::Jumping || player -> get_current_state() == Ientity::Air_state::Falling)
        {
            only_side_movement_allowed = true;
        }

        switch(input)
        {
            case 'W':
                if(only_side_movement_allowed) break;
                player -> set_air_state(Ientity::Air_state::Jumping);
                break;
            case 'w':
                if(only_side_movement_allowed) break;
                player -> set_air_state(Ientity::Air_state::Jumping);
                break;
            case 'A':
                while(step_multiplier > 0)
                {
                    player -> move(Ientity::Movement::Left);
                    step_multiplier--;
                }
                break;
            case 'a':
                while(step_multiplier > 0)
                {
                    player -> move(Ientity::Movement::Left);
                    step_multiplier--;
                }
                break;
            case 'D':
                while(step_multiplier > 0)
                {
                    player -> move(Ientity::Movement::Right);
                    step_multiplier--;
                }
                break;
            case 'd':
                while(step_multiplier > 0)
                {
                    player -> move(Ientity::Movement::Right);
                    step_multiplier--;
                }
                break;
            case char(27):
                exit = true;
                break;
            default:
                break;
        }
    }

    return exit;
}

WINDOW* initial_window_gameplay_output(std::shared_ptr<Ilevel> p_current_level, unsigned int height, unsigned int width)
{
    WINDOW* new_window;
    const unsigned int startX = 1;
    const unsigned int startY = 1;

    new_window = newwin(height, width, startY, startX);
    wborder(new_window, '|', '|', '-', '-', '+', '+', '+' , '+');

    std::istringstream map_layout(p_current_level -> get_current_map_layout());
    std::string temp_line;

    int i = 0;
    while(getline(map_layout, temp_line))
    {
        mvwprintw(new_window, i, 0, temp_line.c_str()); //replacing lines in window with current level's map layout
        i++;
    }

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
    Ientity::Air_state current_air_state = main_player -> get_current_state();

    switch(current_air_state)
    {
        case Ientity::Air_state::Jumping:
            main_player -> jump();
            break;
        case Ientity::Air_state::Falling:
            main_player -> fall();
            break;
        case Ientity::Air_state::None:
            break;
    }

    if((main_player -> get_current_state()) == Ientity::Air_state::None &&
       (main_player -> move(Ientity::Movement::Down)) == true)                  //constant check if falling is available
       {
            main_player -> set_air_state(Ientity::Air_state::Falling);          //constant falling if not on wall
       }

    main_player -> draw(main_player -> get_current_position());
    wmove(operating_window, 0, 0);
    wrefresh(operating_window);
}

std::string map_converter(std::string p_file_name, unsigned int* map_height, unsigned int* map_width) //Converting map layout from .txt file to single string
{
    std::ifstream file(p_file_name);
    if(!file)
    {
        std::cout << "Error reading map file";
    }

    unsigned int width = 0;
    unsigned int height = 0;

    std::string single_line;
    std::string map_converted;

    while(std::getline(file, single_line))
    {
        if(single_line.size() > width)
        {
            width = single_line.size();
        }
        map_converted += single_line + "\n";
        height++;
    }
    *map_width = width+1;
    *map_height = height;
    file.close();
    return map_converted;
}