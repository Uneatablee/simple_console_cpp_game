#pragma once

#include "Tplatform.hpp"
#include "Ilevel.hpp"
#include <iostream>
#include <curses.h>
#include <algorithm>

#include <map>

struct Tposition;

class Tscene : virtual public Ilevel
{
private:

    std::map<unsigned int, Tplatform> m_platforms_container;
    unsigned int m_current_map_height;
    unsigned int m_current_map_width;
    unsigned short m_last_platform_width;
    Tposition m_starting_position;
    Tposition m_last_platform_position;
    std::string m_current_map_layout;

public:

    Tscene() = default;
    Tscene(unsigned int p_height, unsigned int p_width);
    ~Tscene() override = default;

    bool set_starting_position(Tposition position) override;
    bool is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition position) override;
    bool set_last_platform_position(Tposition p_position);
    bool set_last_platform_width(unsigned int p_platform_width);
    bool add_floor() override;
    bool add_platform(Tplatform platform) override;
    bool draw(WINDOW* gameplay) override;
    bool level_movement_down(WINDOW* gameplay_window);
    unsigned int get_current_map_height() override;
    unsigned int get_current_map_width() override;
    std::string get_current_map_layout() override;
    Tposition get_starting_position() override;
    Tposition get_last_platform_position();
    unsigned short get_current_platforms_count();
    unsigned short get_last_platform_width();
};