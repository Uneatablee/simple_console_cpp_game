#include "../include/Tlevel.hpp"

Tlevel::Tlevel(std::shared_ptr<std::string> loaded_map)
{
    m_map = loaded_map;
}

Tlevel::Tlevel()
{
    m_map = nullptr;
}

std::shared_ptr<std::string> Tlevel::get_level_map()
{
    return m_map;
}

bool Tlevel::is_next_pixel_wall(Tposition position)
{
    return true;
}

Tposition Tlevel::get_starting_position()
{
    return m_starting_position;
}
