#include "../include/Tplayer.hpp"

Tplayer::Tplayer()
{
    m_name = "unnamed";
    m_current_position = Tposition(0,0);
}

Tplayer::Tplayer(std::string init_name) : m_name(init_name){}

bool Tplayer::assign_level(std::shared_ptr<Ilevel> current_level_pointer)
{
    this -> m_current_level = current_level_pointer;
    m_current_position = current_level_pointer -> get_starting_position();

    return true;
}

bool Tplayer::move(Movement movement)
{

    return true;
}

std::string Tplayer::get_name()
{
    return m_name;
}

std::shared_ptr<Ilevel> Tplayer::get_current_level()
{
    return m_current_level;
}
