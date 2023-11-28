#pragma once
#include <memory>
#include <string>
#include "../business_logic/include/Idrawable.hpp"

struct Tposition;

class player_drawing_module : virtual public Idrawable
{
public:

    player_drawing_module() = default;
    ~player_drawing_module() override = default;
    bool draw(Tposition position) override;
};