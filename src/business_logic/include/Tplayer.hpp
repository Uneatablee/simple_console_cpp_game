#pragma once
#include "Ientity.hpp"
#include "Ilevel.hpp"
#include "Tposition.hpp"
#include <memory>

class Tplayer : virtual public Ientity
{
private:

    Tposition current_position;
    std::shared_ptr<Ilevel> current_level = nullptr;
    std::string name;

public:

    Tplayer();
    ~Tplayer() override = default;
    Tplayer(std::string name);
    bool assign_level(std::shared_ptr<Ilevel> current_level) override;
    bool move(Movement) override;
    std::string get_name() override;
    std::shared_ptr<Ilevel> get_current_level() override;
};