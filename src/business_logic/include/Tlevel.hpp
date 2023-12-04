#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "Ilevel.hpp"

struct Tposition;

class Tlevel : virtual public Ilevel
{
private:

    std::string m_map;
    Tposition m_starting_position;
    unsigned int m_current_map_height;
    unsigned int m_current_map_width;

public:

    Tlevel() = default;
    ~Tlevel() override = default;

    Tlevel(std::string p_loaded_map, unsigned int map_height, unsigned int map_width);
    bool is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition position) override;
    Tposition get_starting_position() override;
    unsigned int get_current_map_height() override;
    unsigned int get_current_map_width() override;
    std::string get_current_map_layout() override;
    bool set_starting_position(Tposition position) override;
};