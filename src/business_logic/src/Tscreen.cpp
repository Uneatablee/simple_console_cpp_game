#include "../include/Tscreen.hpp"
#include "../include/Tposition.hpp"
#include <thread>
#include <chrono>

Tscreen::Tscreen(char p_background_sign) : m_background_sign(p_background_sign)
{
    std::string space(m_width - 1,m_background_sign);
    for(unsigned int i = 0; i < m_height; i++)
    {
        m_screen_output += space + "\n";
    }
}

bool Tscreen::main_screen_output()
{
    std::cout << m_screen_output << std::flush;
    return true;
}

std::string Tscreen::get_char(Tposition position)
{
    std::string character = m_screen_output.substr(position.m_position_y * m_width + position.m_position_x, 1);
    return character;
}

bool Tscreen::screen_replace(std::string replacement, Tposition position)
{
    int replacement_start_index = position.m_position_y * m_width + position.m_position_x;
    m_screen_output.replace(replacement_start_index, replacement.length(), replacement);
    return true;
}

bool Tscreen::refresh()
{

    std::cout << std::flush;
    system("clear");
    std::cout <<  this -> m_screen_output << std::flush;
    return true;
}

bool Tscreen::clear_content()
{
    m_screen_output = "";
    std::string space(m_width - 1,m_background_sign);
    for(unsigned int i = 0; i < m_height; i++)
    {
        m_screen_output += space + "\n";
    }

    return true;
}