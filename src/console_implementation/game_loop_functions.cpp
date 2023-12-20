#include "main_header.hpp"

bool exit_value = false;  //condition of game_loops (game_loop with render, update and input_loop) working
unsigned short speed_limiter = 10; //speed of map travelling down
unsigned short map_speed_interval = 500; //after 500 game_loop iterations -> speeding up

bool gameloop()
{
    starting_screen();
    unsigned int gameplay_window_height;
    unsigned int gameplay_window_width;

    std::shared_ptr<Tscene> self_generating_level = std::make_shared<Tscene>(40, 140); //test width and height values
    self_generating_level -> set_starting_position(Tposition(20,20));

    //windows setup
    auto scoreboard_window = initial_window_scoreboard_output();
    auto gameplay_window = initial_window_gameplay_output(self_generating_level, 40, 141);

    //player setup
    auto main_player = std::make_shared<drawable_player>(gameplay_window.get(), "main_player");

    //main_player -> assign_level(starting_level);
    main_player -> assign_level(self_generating_level);

    //GAME LOOP <------------------->
    std::thread input_process(input_processing, main_player); //--> extracted from game loop ---> its not blocking game updating

    while(!exit_value)
    {
        exit_value = update(gameplay_window.get(),scoreboard_window.get(), main_player, self_generating_level); //--> one step forward all movement mechanics

        //render(); --> rendering with delta time ---> colours and Ansi codes generator
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout <<"\nGame Over!\n";

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
    mvwprintw(new_window.get(), 5, 8, "SCORE:");
    wrefresh(new_window.get());

    return new_window;
}

bool update(WINDOW* const operating_window,WINDOW* const scoreboard, std::shared_ptr<drawable_player> main_player, std::shared_ptr<Tscene> p_current_level)
{
    bool play_over = false;
    static unsigned int counter = 0;
    static int height_register = 0;
    static unsigned int best_score = 0;

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

    //map random generating and sliding down
    unsigned short current_platforms_count = p_current_level -> get_current_platforms_count();
    if(current_platforms_count)
    {
        p_current_level -> add_platform(random_platform_generator(p_current_level));
    }

    //output
    p_current_level -> draw(operating_window);

    if(counter % speed_limiter == 0)  //once in a n loops platforms moving down. Add constant miliseconds interval later (delta time).
    {
        p_current_level -> level_movement_down(operating_window);
        height_register++;
    }
    counter++;
    if(counter > map_speed_interval && speed_limiter >= 0)
    {
        speed_limiter -= 2;
        map_speed_interval *= 2;
    }

    main_player -> draw();

    if(main_player -> get_current_position().m_position_y > p_current_level -> get_current_map_height() + 1)
    {
        play_over = true;
    }
    unsigned int current_player_height =  (p_current_level -> get_current_map_height()) - (main_player -> get_current_position().m_position_y);

    if(current_player_height + height_register > best_score)
    {
        best_score = current_player_height + height_register;
        mvwprintw(scoreboard, 6, 8, (std::to_string(best_score)).c_str());
        wrefresh(scoreboard);
    }

    border_refresh(operating_window, p_current_level);
    wmove(operating_window, 0, 0);
    wrefresh(operating_window);
    return play_over;
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

Tplatform random_platform_generator(std::shared_ptr<Tscene> current_scene)
{
    std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
    auto duration_since_epoch = current_time.time_since_epoch();
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch).count());

    //next platform generation base coorrdinates:
    unsigned int horizontal_spacing = 5;   //max horizontal spacing between next platforms
    unsigned int vertical_spacing = 5;     //max vertical spacing between platfroms

    unsigned int left_x_range = current_scene -> get_last_platform_position().m_position_x - horizontal_spacing;
    unsigned int right_x_range = current_scene -> get_last_platform_position().m_position_x + current_scene -> get_last_platform_width() + horizontal_spacing;

    if(left_x_range < 2)
    {
        left_x_range = 2;
    }

    if(right_x_range > current_scene -> get_current_map_width() - 4)
    {
        right_x_range = current_scene -> get_current_map_width() - 4;
    }

    int next_y_position = current_scene -> get_last_platform_position().m_position_y - vertical_spacing;
    unsigned int next_x_position = (rand() % (right_x_range - left_x_range)) + left_x_range + 1;

    unsigned short min_platform_width = 3;
    unsigned short max_platform_width = 16;
    unsigned short next_platform_width = (rand() % (max_platform_width - min_platform_width)) + min_platform_width + 1;

    if(next_x_position + next_platform_width > current_scene -> get_current_map_width() - 4)
    {
        next_platform_width = (current_scene -> get_current_map_width() - next_x_position - 1);
        next_x_position = next_x_position - 20;
    }

    Tposition new_platform_position(next_x_position, next_y_position);
    current_scene -> set_last_platform_position(new_platform_position);
    Tplatform new_platform(new_platform_position, 1, next_platform_width);

    return new_platform;
}

bool border_refresh(WINDOW* gameplay_window, std::shared_ptr<Tscene> p_current_level)
{
    std::string frame(p_current_level -> get_current_map_width(), '#');
    mvwprintw(gameplay_window, p_current_level -> get_current_map_height() - 1, 0, frame.c_str());
    mvwprintw(gameplay_window, 0, 0, frame.c_str());
    return true;
}

bool starting_screen()
{
    const unsigned int startX = 1;
    const unsigned int startY = 1;
    auto new_window = std::unique_ptr<WINDOW, std::function<void(WINDOW*)>>(
        newwin(40, 140 - 1, startY, startX),
        [](WINDOW* win)
        {
            delwin(win);
        });

    wborder(new_window.get(), '|', '|', '-', '-', '+', '+', '+', '+');

    std::vector<std::string> logo_container{};
    logo_container.push_back("       __   __    __  .___  ___. .______");
    logo_container.push_back("      |  | |  |  |  | |   \\/   | |   _  \\");
    logo_container.push_back("      |  | |  |  |  | |  \\  /  | |  |_)  | ");
    logo_container.push_back(".--.  |  | |  |  |  | |   \\/|  | |   ___/  ");
    logo_container.push_back("|  `--'  | |  `--'  | |  |  |  | |  |  ");
    logo_container.push_back(" \\______/   \\______/  |__|  |__| | _| ");

    logo_container.push_back("  _______ .______        ______     _______ ");
    logo_container.push_back(" |   ____||   _  \\      /  __  \\   /  _____|");
    logo_container.push_back(" |  |__   |  |_)  |    |  |  |  | |  |  __");
    logo_container.push_back(" |   __|  |      /     |  |  |  | |  | |_ |");
    logo_container.push_back(" |  |     |  |\\  \\----.|  `--'  | |  |__| |");
    logo_container.push_back(" |__|     | _| `._____| \\______/   \\______|");

    int i = 0;
    for(auto elem : logo_container)
    {
        mvwprintw(new_window.get(), 14 + i, 58, elem.c_str());
        i++;
        wrefresh(new_window.get());
    }

    for(int j = 0; j < 50; j++)
    {
        i = 0;
        for(auto elem : logo_container)
        {
            std::string temp(elem.length(),' ');
            mvwprintw(new_window.get(), 14 + i, 58 - j + 1, temp.c_str());
            mvwprintw(new_window.get(), 14 + i, 58 - j, elem.c_str());
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        wrefresh(new_window.get());
    }

    std::vector<std::string> countdown_container{};
    countdown_container.push_back(" ____");
    countdown_container.push_back("|___  \\");
    countdown_container.push_back(" ___) | ");
    countdown_container.push_back("|__  < ");
    countdown_container.push_back(" ___) |  ");
    countdown_container.push_back("|____/  ");

    countdown_container.push_back(" ___  ");
    countdown_container.push_back("|__ \\ ");
    countdown_container.push_back("   ) |");
    countdown_container.push_back("  / / ");
    countdown_container.push_back(" / /_ ");
    countdown_container.push_back("|____|");

    countdown_container.push_back(" __");
    countdown_container.push_back("/_ |");
    countdown_container.push_back(" | |");
    countdown_container.push_back(" | |");
    countdown_container.push_back(" | |");
    countdown_container.push_back(" |_|");

    std::string cleaner("          ");

    int line = 0;
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j < 6 ; j++)
        {
            mvwprintw(new_window.get(), 17 + j, 100, cleaner.c_str());
            mvwprintw(new_window.get(), 17 + j, 100, countdown_container[line].c_str());
            line++;
        }
        wrefresh(new_window.get());
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
    return true;
}