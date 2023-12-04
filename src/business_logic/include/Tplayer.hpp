#pragma once
#include "Ientity.hpp"
#include "Tposition.hpp"
#include <memory>
#include <iostream>

struct Tposition;
class Ilevel;

class Tplayer : virtual public Ientity
{
private:

    #define STARTING_JUMP_VELOCITY 3

    Air_state m_current_air_state = Air_state::None;
    Tposition m_current_position;
    std::shared_ptr<Ilevel> m_current_level = nullptr;
    std::string m_name;
    int m_current_jump_velocity = STARTING_JUMP_VELOCITY; //velocity as [rows per loop] ----> jumping and falling speed
    const double m_gravity_constance = -1;  //acceleration as [(rows/loop)/loop] ----> imitation of gravity

public:

    Tplayer(std::string init_name);
    ~Tplayer() override = default;

    bool move(Movement) override;
    bool jump() override;
    bool fall() override;
    bool assign_level(std::shared_ptr<Ilevel> p_current_level) override;
    bool change_current_position(Tposition position) override;
    bool set_air_state(Air_state state) override;
    std::string get_name() override;
    Tposition get_current_position() override;
    std::shared_ptr<Ilevel> get_current_level() override;
    Air_state get_current_state() override;
};