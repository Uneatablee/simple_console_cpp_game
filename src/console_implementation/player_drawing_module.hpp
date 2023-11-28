#pragma once
#include <memory>
#include <string>
#include "../business_logic/include/Idrawable.hpp"

class Tscreen;
struct Tposition;

class player_drawing_module : virtual public Idrawable
{
public:

    player_drawing_module() = default;
    ~player_drawing_module() override = default;
    bool draw(const std::shared_ptr<Tscreen>& screen, Tposition position) override;
};