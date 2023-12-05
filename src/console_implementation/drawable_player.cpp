#include "drawable_player.hpp"
#include "Tposition.hpp"

drawable_player::drawable_player(WINDOW* gameplay_window, std::string init_name) : Tplayer(init_name), m_gameplay_window(gameplay_window)
{}

bool drawable_player::draw(Tposition p_current_player_position)
{
    static Tposition previous_position = Tposition(0,0);
    if(previous_position.m_position_x != 0 && previous_position.m_position_y != 0)
    {
        mvwprintw(m_gameplay_window, previous_position.m_position_y, previous_position.m_position_x, "     ");
        mvwprintw(m_gameplay_window, previous_position.m_position_y - 1, previous_position.m_position_x + 1, "   ");
    }

    mvwprintw(m_gameplay_window, p_current_player_position.m_position_y, p_current_player_position.m_position_x, m_bottom_body);
    mvwprintw(m_gameplay_window, p_current_player_position.m_position_y - 1, p_current_player_position.m_position_x + 1, m_top_body);

    previous_position = p_current_player_position;
    return true;
}