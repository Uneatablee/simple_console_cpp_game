#pragma once
#include <string>
#include <memory>

class Ilevel;
struct Tposition;

class Ientity
{
public:

    enum class Movement
    {
        Up,
        Down,
        Left,
        Right
    };

    enum class Air_state
    {
        Jumping,
        None,
        Falling
    };

    Ientity() = default;
    virtual ~Ientity() = default;

    Ientity(const Ientity& object) = default;
    Ientity& operator=(const Ientity& object) = default;

    Ientity(Ientity&& object) = default;
    Ientity& operator=(Ientity&& object) = default;

    virtual bool move(Movement direction) = 0;
    virtual std::string get_name() = 0;
    virtual bool assign_level(std::shared_ptr<Ilevel> current_level) = 0;
    virtual std::shared_ptr<Ilevel> get_current_level() = 0;
    virtual Tposition get_current_position() = 0;
    virtual bool change_current_position(Tposition position) = 0;
    virtual Air_state get_current_state() = 0;
    virtual bool jump() = 0;
    virtual bool fall() = 0;
    virtual bool set_air_state(Air_state state) = 0;

};