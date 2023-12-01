#pragma once
#include "Ientity.hpp"
#include "Ilevel.hpp"
#include <memory>

struct Tposition;

class Tplayer : virtual public Ientity
{
private:

    Tposition m_current_position;
    std::shared_ptr<Ilevel> m_current_level = nullptr;
    std::string m_name;

public:

    Tplayer(std::string init_name);
    ~Tplayer() override = default;
    bool assign_level(std::shared_ptr<Ilevel> p_current_level) override;
    bool move(Movement) override;
    std::string get_name() override;
    std::shared_ptr<Ilevel> get_current_level() override;
    Tposition get_current_position() override;
    bool change_current_position(Tposition position) override;
};