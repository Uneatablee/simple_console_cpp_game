
#include "../include/Tlevel.hpp"

Tlevel::Tlevel(std::string loaded_map, unsigned int p_map_width, unsigned int p_map_height)
{
    m_map = loaded_map;
    m_current_map_height = p_map_height;
    m_current_map_width = p_map_width;
}

bool Tlevel::is_next_pixel_wall(Tposition position)
{
    return true;
}

Tposition Tlevel::get_starting_position()
{
    return m_starting_position;
}

unsigned int Tlevel::get_current_map_height()
{
    return m_current_map_height;
}

unsigned int Tlevel::get_current_map_width()
{
    return m_current_map_width;
}

std::string Tlevel::get_current_map_layout()
{
    return m_map;
}
