#pragma once
#include "Iobstacle.hpp"
#include "Tposition.hpp"

class Tplatform : virtual public Iobstacle
{
private:

    Tposition m_position_coordinates;
    unsigned int m_height;
    unsigned int m_width;

public:

    Tplatform() = default;
    ~Tplatform() override = default;
    Tplatform(Tposition p_coordinates, unsigned int p_height, unsigned int p_width);

    unsigned int get_height() override;
    unsigned int get_width() override;
    Tposition get_position() override;
};