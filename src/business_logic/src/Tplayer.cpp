#include "../include/Tplayer.hpp"

Tplayer::Tplayer()
{
    name = "unnamed";
    current_position = Tposition(0,0);
}

Tplayer::Tplayer(std::string init_name) : name(init_name){}

bool Tplayer::assign_level(std::shared_ptr<Ilevel> current_level_pointer)
{
    this -> current_level = current_level_pointer;
    current_position = current_level_pointer -> get_starting_position();

    return true;
}

bool Tplayer::move(Movement movement)
{

    return true;
}

std::string Tplayer::get_name()
{
    return name;
}

std::shared_ptr<Ilevel> Tplayer::get_current_level()
{
    return current_level;
}
