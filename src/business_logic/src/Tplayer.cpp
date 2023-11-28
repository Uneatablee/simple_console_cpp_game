#include "../include/Tplayer.hpp"
#include "../include/Tposition.hpp"

Tplayer::Tplayer(std::string init_name, const std::shared_ptr<Idrawable>& drawer)
{
    m_drawer = drawer;
    m_name = init_name;
    m_current_position = Tposition(0,0);
}

bool Tplayer::assign_level(std::shared_ptr<Ilevel> current_level_pointer)
{
    this -> m_current_level = current_level_pointer;
    m_current_position = current_level_pointer -> get_starting_position();

    return true;
}

bool Tplayer::move(Movement movement)
{
    switch(movement)
    {
        case Movement::Up:
            m_current_position.m_position_y += 1;
            break;
        case Movement::Down:
            m_current_position.m_position_y -= 1;
            break;
        case Movement::Left:
            m_current_position.m_position_x -= 1;
            break;
        case Movement::Right:
            m_current_position.m_position_x += 1;
            break;
    }

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

Tposition Tplayer::get_current_position()
{
    return m_current_position;
}

bool Tplayer::draw(const std::shared_ptr<Tscreen>& screen, Tposition position)
{
    m_drawer -> draw(screen, position);

    return true;
}

bool Tplayer::change_current_position(Tposition position)
{
    m_current_position = position;
    return true;
}
