#include "../include/Tlevel.hpp"

Tlevel::Tlevel(std::shared_ptr<std::string> loaded_map)
{
    map = loaded_map;
}

Tlevel::Tlevel()
{
    map = nullptr;
}

std::shared_ptr<std::string> Tlevel::get_level_map()
{
    return map;
}

bool Tlevel::is_next_pixel_wall(int position_x, int position_y)
{
    return true;
}

Tposition Tlevel::get_starting_position()
{
    return starting_position;
}
