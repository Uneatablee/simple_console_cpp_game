#pragma once

struct Tposition
{
public:

    int m_position_x;
    int m_position_y;

    Tposition() = default;
    ~Tposition() = default;

    Tposition(const Tposition& object) = default;
    Tposition& operator=(const Tposition& object) = default;

    Tposition(Tposition&& object) = default;
    Tposition& operator=(Tposition&& object) = default;
    Tposition(int x, int y) : m_position_x(x), m_position_y(y){}

    bool operator==(Tposition p_position) const
    {
        if(this -> m_position_x == p_position.m_position_x &&
           this -> m_position_y == p_position.m_position_y)
           {
                return true;
           }

           return false;
    }
};