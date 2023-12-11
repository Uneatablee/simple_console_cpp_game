#include "../include/Tscene.hpp"

bool Tscene::set_starting_position(Tposition p_position)
{
    m_starting_position = p_position;
    return true;
}

bool Tscene::is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition position)
{
    return true;
}

unsigned int Tscene::get_current_map_height()
{
    return m_current_map_height;
}

unsigned int Tscene::get_current_map_width()
{
    return m_current_map_width;
}

std::string Tscene::get_current_map_layout()
{
    return std::string("");
}

Tposition Tscene::get_starting_position()
{
    return m_starting_position;
}

Tposition Tscene::get_last_platform_position()
{
    return m_last_platform_position;
}
