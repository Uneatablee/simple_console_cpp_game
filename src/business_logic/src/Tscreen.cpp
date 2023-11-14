#include "../include/Tscreen.hpp"

Tscreen::Tscreen()
{
    std::string space(width - 1,'.');
    for(unsigned int i = 0; i < height; i++)
    {
        screen_output += space + '\n';
    }
}

bool Tscreen::main_screen_output()
{
    std::cout << screen_output << std::endl;
    return true;
}

std::string Tscreen::get_char(int position_x, int position_y)
{
    std::string character = screen_output.substr(position_y * width + position_x, 1);
    return character;
}

bool Tscreen::screen_replace(std::string replacement, int position_x, int position_y)
{
    int replacement_start_index = position_y * width + position_x;
    screen_output.replace(replacement_start_index, replacement.length(), replacement);
    return true;
}