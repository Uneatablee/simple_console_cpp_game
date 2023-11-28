#pragma once
#include <iostream>
#include <memory>

class Tscreen;
struct Tposition;

class Idrawable
{
public:

    Idrawable() = default;
    virtual ~Idrawable() = default;

    Idrawable(const Idrawable& object) = default;
    Idrawable& operator=(const Idrawable& object) = default;

    Idrawable(Idrawable&& object) = default;
    Idrawable& operator=(Idrawable && object) = default;

    virtual bool draw(const std::shared_ptr<Tscreen>& screen, Tposition position) = 0;

};