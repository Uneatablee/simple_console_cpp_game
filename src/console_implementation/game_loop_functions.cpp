#include "main_header.hpp"

bool exit_value = false;  //condition of game_loops (game_loop with render, update and input_loop) working

bool gameloop()
{
    unsigned int gameplay_window_height;
    unsigned int gameplay_window_width;

    //map setup
    std::string map_name = "level_1_map.txt";
    std::tuple map_layout = map_converter(map_name); //converting file and getting single string, height and width of gamepolay window

    std::string map_layout_converted = std::get<0>(map_layout);
    gameplay_window_height = std::get<1>(map_layout);
    gameplay_window_width = std::get<2>(map_layout);

    //starting level setup
    std::shared_ptr<Ilevel> starting_level = std::make_shared<Tlevel>(map_layout_converted, gameplay_window_height, gameplay_window_width);
    starting_level -> set_starting_position(Tposition(20,20));

    //windows setup

    auto scoreboard_window = initial_window_scoreboard_output();
    auto gameplay_window = initial_window_gameplay_output(starting_level, gameplay_window_height, gameplay_window_width);

    //player setup
    auto main_player = std::make_shared<drawable_player>(gameplay_window.get(), "main_player");
    main_player -> assign_level(starting_level);

    //GAME LOOP <------------------->
    std::thread input_process(input_processing, main_player); //--> extracted from game loop ---> its not blocking game updating

    while(!exit_value)
    {
        update(gameplay_window.get(), main_player); //--> one step forward all movement mechanics

        //render(); --> rendering with delta time ---> colours and Ansi codes generator
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    //clearing
    input_process.join();

    return false;
}

bool input_processing(const std::shared_ptr<Ientity>& player)
{
    int input;
    bool only_side_movement_allowed = false;
    unsigned int step_multiplier = 4;    //left and right step length

    while(!exit_value)
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
                exit_value = true;
                break;
            default:
                break;
        }
    }

    return true;
}

std::unique_ptr<WINDOW, std::function<void(WINDOW*)>> initial_window_gameplay_output(
    std::shared_ptr<Ilevel> p_current_level, unsigned int height, unsigned int width)
{
    const unsigned int startX = 1;
    const unsigned int startY = 1;
    auto new_window = std::unique_ptr<WINDOW, std::function<void(WINDOW*)>>(
        newwin(height, width - 1, startY, startX),
        [](WINDOW* win)
        {
            delwin(win);
        });

    wborder(new_window.get(), '|', '|', '-', '-', '+', '+', '+', '+');

    std::istringstream map_layout(p_current_level -> get_current_map_layout());
    std::string temp_line;

    int i = 0;
    while(getline(map_layout, temp_line))
    {
        mvwprintw(new_window.get(), i, 0, temp_line.c_str()); //replacing lines in window with current level's map layout
        i++;
    }

    wrefresh(new_window.get());
    return new_window;
}

std::unique_ptr<WINDOW, decltype(WINDOW_deleter)> initial_window_scoreboard_output()
{
    const unsigned int height = 40;
    const unsigned int width = 20;
    const unsigned int startX = 142;
    const unsigned int startY = 1;

    auto new_window = std::unique_ptr<WINDOW, decltype(WINDOW_deleter)>(
        newwin(height, width, startY, startX),
        WINDOW_deleter);

    wborder(new_window.get(), '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(new_window.get());

    return new_window;
}

void update(WINDOW* const operating_window, std::shared_ptr<drawable_player> main_player)
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

    //map random generating and sliding down -->

    main_player -> draw();
    wmove(operating_window, 0, 0);
    wrefresh(operating_window);
}

std::tuple<std::string, unsigned int, unsigned int> map_converter(std::string p_file_name) //Converting map layout from .txt file to single string
{
    std::ifstream file(p_file_name);
    if(!file)
    {
        std::cout << "Error reading map file";
        throw std::exception();
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
    width = width + 1; //for additional endline
    file.close();
    return {map_converted, height, width};
}