#pragma once

struct Tposition;

class Iobstacle
{
public:

    Iobstacle() = default;
    virtual ~Iobstacle() = default;

    Iobstacle(const Iobstacle& object) = default;
    Iobstacle& operator=(const Iobstacle& object) = default;

    Iobstacle(Iobstacle&& object) = default;
    Iobstacle& operator=(Iobstacle&& object) = default;

    virtual unsigned int get_height() = 0;
    virtual unsigned int get_width() = 0;
    virtual Tposition get_position() = 0;
    virtual bool change_position(Tposition position) = 0;
};