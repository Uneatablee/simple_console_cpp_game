#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "Ilevel.hpp"
#include "Tposition.hpp"

class Tlevel : virtual public Ilevel
{
private:

    std::shared_ptr<std::string> map;
    Tposition starting_position;

public:

    Tlevel();
    Tlevel(std::shared_ptr<std::string> loaded_map);
    std::shared_ptr<std::string> get_level_map();
    bool is_next_pixel_wall(int position_x, int position_y);
    Tposition get_starting_position();
};