#include "../include/Tplatform.hpp"

Tplatform::Tplatform(Tposition p_platform_position, unsigned int p_height, unsigned int p_width) : m_position_coordinates(p_platform_position) ,
m_height(p_height), m_width(p_width)
{

}

unsigned int Tplatform::get_height()
{
    return m_height;
}

unsigned int Tplatform::get_width()
{
    return m_width;
}

Tposition Tplatform::get_position()
{
    return m_position_coordinates;
}

bool Tplatform::change_position(Tposition p_position)
{
    m_position_coordinates.m_position_x = p_position.m_position_x;
    m_position_coordinates.m_position_y = p_position.m_position_y;

    return true;
}