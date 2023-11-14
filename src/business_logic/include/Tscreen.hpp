#pragma once
#include <iostream>
#include <string>

class Tscreen
{

protected:

    std::string screen_output;
    const unsigned int width = 121;
    const unsigned int height = 40;

public:

    Tscreen();
    ~Tscreen() = default;

    Tscreen(const Tscreen& object) = default;
    Tscreen& operator=(const Tscreen& object) = default;

    Tscreen(Tscreen&& object) = default;
    Tscreen& operator=(Tscreen&& object) = default;

    bool main_screen_output();
    std::string get_char(int position_x, int position_y);
    bool screen_replace(std::string replacement, int position_x, int position_y);
};