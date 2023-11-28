#include "player_drawing_module.hpp"
#include "../business_logic/include/Tscreen.hpp"
#include "../business_logic/include/Tposition.hpp"

bool player_drawing_module::draw(const std::shared_ptr<Tscreen>& screen, Tposition p_position)
{
    //player body:
    std::string top =    "o--o";
    std::string middle = "|~~|";

    Tposition middle_position(p_position.m_position_x, p_position.m_position_y+1);

    screen -> screen_replace(top,p_position);
    screen -> screen_replace(middle, middle_position);

    return true;
}