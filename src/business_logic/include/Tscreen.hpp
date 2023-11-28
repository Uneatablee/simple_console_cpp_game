#pragma once
#include <iostream>
#include <string>

struct Tposition;

class Tscreen
{

protected:

    std::string m_screen_output;
    char m_background_sign;
    unsigned int m_width = 71;
    unsigned int m_height = 30;

public:

    Tscreen(char p_background_sign = '.');
    ~Tscreen() = default;

    Tscreen(const Tscreen& object) = default;
    Tscreen& operator=(const Tscreen& object) = default;

    Tscreen(Tscreen&& object) = default;
    Tscreen& operator=(Tscreen&& object) = default;

    bool main_screen_output();
    std::string get_char(Tposition position);
    bool screen_replace(std::string replacement,Tposition position);
    bool refresh();
    bool clear_content();
};