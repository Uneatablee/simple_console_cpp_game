#pragma once
#include <string>
#include <memory>

class Ilevel;

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

    Ientity() = default;
    virtual ~Ientity() = default;

    Ientity(const Ientity& object) = default;
    Ientity& operator=(const Ientity& object) = default;

    Ientity(Ientity&& object) = default;
    Ientity& operator=(Ientity&& object) = default;

    virtual bool move(Movement) = 0;
    virtual std::string get_name() = 0;
    virtual bool assign_level(std::shared_ptr<Ilevel> current_level) = 0;
    virtual std::shared_ptr<Ilevel> get_current_level() = 0;

};