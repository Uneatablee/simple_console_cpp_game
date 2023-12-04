#include "main_header.hpp"


bool gameloop()
{
    unsigned int gameplay_window_height;
    unsigned int gameplay_window_width;

    std::string map_name = "level_1_map.txt";
    std::string map_layout = map_converter(map_name, &gameplay_window_height, &gameplay_window_width); //converting file and getting single string, height and width of gamepolay window

    std::shared_ptr<Ilevel> starting_level = std::make_shared<Tlevel>(map_layout, gameplay_window_height, gameplay_window_width);

    WINDOW* gameplay_window;
    WINDOW* scoreboard_window;
    scoreboard_window = initial_window_scoreboard_output();
    gameplay_window = initial_window_gameplay_output(starting_level,gameplay_window_height, gameplay_window_width);

    std::shared_ptr<drawable_player> main_player = std::make_shared<drawable_player>(gameplay_window, "main_player");
    main_player -> change_current_position(Tposition(20,20));




    while(true)
    {
        input_processing(main_player);  // --->  get input_processing as separate thread later
        update(gameplay_window, main_player); //--> one step forward all movement mechanics

        //render(); --> rendering with delta time
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }




    delwin(gameplay_window);
    delwin(scoreboard_window);


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
            case 'p':
                std::cout <<" , ";
                std::cout << player ->get_current_position().m_position_x <<", " << player ->get_current_position().m_position_y;
            case char(27):
                exit = true;
                break;
            default:
                break;
        }
    //}

    return exit;
}

WINDOW* initial_window_gameplay_output(std::shared_ptr<Ilevel> p_current_level, unsigned int height = 40, unsigned int width = 140)
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
    *map_width = width;
    *map_height = height;
    file.close();

    return map_converted;
}