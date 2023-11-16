#pragma once

class Tposition
{
public:

    int position_x;
    int position_y;

    Tposition() = default;
    ~Tposition() = default;

    Tposition(const Tposition& object) = default;
    Tposition& operator=(const Tposition& object) = default;

    Tposition(Tposition&& object) = default;
    Tposition& operator=(Tposition&& object) = default;
    Tposition(int x, int y) : position_x(x), position_y(y){}
};