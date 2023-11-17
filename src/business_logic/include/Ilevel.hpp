#pragma once
#include <string>
#include <memory>
#include "Tposition.hpp"


class Ilevel
{
public:

    Ilevel();
    virtual ~Ilevel() = 0;

    Ilevel(const Ilevel& object) = default;
    Ilevel& operator=(const Ilevel& object) = default;

    Ilevel(Ilevel&& object) = default;
    Ilevel& operator=(Ilevel&& object) = default;

    Ilevel(std::shared_ptr<std::string> loaded_map);
    virtual std::shared_ptr<std::string> get_level_map() = 0;
    virtual bool is_next_pixel_wall(Tposition position) = 0;
    virtual Tposition get_starting_position() = 0;
};