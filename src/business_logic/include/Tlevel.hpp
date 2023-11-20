#pragma once
#include <string>
#include <iostream>
#include <memory>

#include "Ilevel.hpp"

struct Tposition;

class Tlevel : virtual public Ilevel
{
private:

    std::shared_ptr<std::string> m_map;
    Tposition m_starting_position;

public:

    Tlevel();
    Tlevel(std::shared_ptr<std::string> p_loaded_map);
    std::shared_ptr<std::string> get_level_map() override;
    bool is_next_pixel_wall(Tposition position) override;
    Tposition get_starting_position() override;
};