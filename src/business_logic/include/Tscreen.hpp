#pragma once
#include <iostream>
#include <string>

class Tposition;

class Tscreen
{

protected:

    std::string m_screen_output;
    unsigned int m_width = 151;
    unsigned int m_height = 40;

public:

    Tscreen();
    ~Tscreen() = default;

    Tscreen(const Tscreen& object) = default;
    Tscreen& operator=(const Tscreen& object) = default;

    Tscreen(Tscreen&& object) = default;
    Tscreen& operator=(Tscreen&& object) = default;

    bool main_screen_output();
    std::string get_char(Tposition position);
    bool screen_replace(std::string replacement,Tposition position);
};