#pragma once
#include <string>
#include <memory>
#include "Tposition.hpp"
#include "Ientity.hpp"
#include <curses.h>

class Tplatform;

class Ilevel
{
public:

    Ilevel() = default;
    virtual ~Ilevel() = default;

    Ilevel(const Ilevel& object) = default;
    Ilevel& operator=(const Ilevel& object) = default;

    Ilevel(Ilevel&& object) = default;
    Ilevel& operator=(Ilevel&& object) = default;

    virtual bool set_starting_position(Tposition position) = 0;
    virtual bool is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition position) = 0;
    virtual bool add_floor() = 0;
    virtual bool add_platform(Tplatform platform) = 0;
    virtual bool draw(WINDOW* gameplaywindow) = 0;
    virtual unsigned int get_current_map_height() = 0;
    virtual unsigned int get_current_map_width() = 0;
    virtual std::string get_current_map_layout() = 0;
    virtual Tposition get_starting_position() = 0;

};