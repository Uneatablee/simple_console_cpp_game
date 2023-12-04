#pragma once
#include "Ientity.hpp"
#include "Tposition.hpp"
#include <memory>

struct Tposition;
class Ilevel;

class Tplayer : virtual public Ientity
{
private:

    Air_state m_current_air_state = Air_state::None;
    Tposition m_current_position;
    std::shared_ptr<Ilevel> m_current_level = nullptr;
    std::string m_name;
    int m_current_acceleration = 0; //acceleration [rows per loop] ----> imitation of gravity

public:

    Tplayer(std::string init_name);
    ~Tplayer() override = default;

    bool assign_level(std::shared_ptr<Ilevel> p_current_level) override;
    bool move(Movement) override;
    std::string get_name() override;
    std::shared_ptr<Ilevel> get_current_level() override;
    Tposition get_current_position() override;
    bool change_current_position(Tposition position) override;
    Air_state get_current_state() override;
};