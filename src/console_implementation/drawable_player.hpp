#pragma once
#include <memory>
#include <string>
#include "Idrawable.hpp"
#include <curses.h>
#include "../business_logic/include/Tplayer.hpp"

struct Tposition;

class drawable_player : virtual public Idrawable, virtual public Tplayer
{
private:

    WINDOW* m_gameplay_window;
    const char* m_top_body =     "O-O";
    const char* m_bottom_body = "o|~|o";

public:

    drawable_player(WINDOW* gameplay_window, std::string init_name);
    ~drawable_player() override = default;

    bool draw() override;
};