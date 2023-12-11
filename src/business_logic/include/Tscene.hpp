#pragma once

#include "Tplatform.hpp"
#include "Ilevel.hpp"

#include <map>

struct Tposition;

class Tscene : virtual public Ilevel
{
private:

    std::map<Tposition, Tplatform> m_platfroms_container;
    unsigned int m_current_map_height;
    unsigned int m_current_map_width;
    Tposition m_starting_position;
    Tposition m_last_platform_position;

public:

    Tscene() = default;
    ~Tscene() override = default;

    bool set_starting_position(Tposition position) override;
    bool is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition position) override;
    unsigned int get_current_map_height() override;
    unsigned int get_current_map_width() override;
    std::string get_current_map_layout() override;
    Tposition get_starting_position() override;
    Tposition get_last_platform_position();
};