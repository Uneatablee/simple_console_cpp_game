#pragma once
#include <iostream>
#include <memory>

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

    virtual bool draw() = 0;

};