
#include "../include/Tlevel.hpp"

Tlevel::Tlevel(std::string loaded_map, unsigned int p_map_height, unsigned int p_map_width)
{
    m_map = loaded_map;
    m_current_map_height = p_map_height;
    m_current_map_width = p_map_width;
}

bool Tlevel::is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition current_position)
{
    std::string map_layout = this -> get_current_map_layout();

    unsigned int character_index_1 = 0;
    unsigned int character_index_2 = 0;
    unsigned int character_index_3 = 0;
    unsigned int helping_index_1 = 0;    //two helping indexes added for frog legs
    unsigned int helping_index_2 = 0;

    switch(inputed_movement)
    {
        case Ientity::Movement::Up:
            character_index_1 = (m_current_map_width) * (current_position.m_position_y - 1) + current_position.m_position_x;
            character_index_2 = (m_current_map_width) * (current_position.m_position_y - 2) + current_position.m_position_x + 1;
            character_index_3 = (m_current_map_width) * (current_position.m_position_y - 2) + current_position.m_position_x + 2;
            helping_index_1 = (m_current_map_width) * (current_position.m_position_y - 2) + current_position.m_position_x + 3;
            helping_index_2 = (m_current_map_width) * (current_position.m_position_y - 1) + current_position.m_position_x + 4;
            break;
        case Ientity::Movement::Down:
            character_index_1 = (m_current_map_width) * (current_position.m_position_y + 1) + current_position.m_position_x;
            character_index_2 = (m_current_map_width) * (current_position.m_position_y + 1) + current_position.m_position_x + 1;
            character_index_3 = (m_current_map_width) * (current_position.m_position_y + 1) + current_position.m_position_x + 2;
            helping_index_1 = (m_current_map_width) * (current_position.m_position_y + 1) + current_position.m_position_x + 3;
            helping_index_2 = (m_current_map_width) * (current_position.m_position_y + 1) + current_position.m_position_x + 4;
            break;
        case Ientity::Movement::Left:
            character_index_1 = (m_current_map_width) * (current_position.m_position_y) + current_position.m_position_x - 1;
            character_index_2 = (m_current_map_width) * (current_position.m_position_y - 1) + current_position.m_position_x - 2;
            character_index_3 = character_index_1;
            helping_index_1 = character_index_1;
            helping_index_2 = character_index_1;
            break;
        case Ientity::Movement::Right:
            character_index_1 = (m_current_map_width) * (current_position.m_position_y) + current_position.m_position_x + 3;
            character_index_2 = (m_current_map_width) * (current_position.m_position_y) + current_position.m_position_x + 5;
            character_index_3 = (m_current_map_width) * (current_position.m_position_y - 1) + current_position.m_position_x + 4;
            helping_index_1 = character_index_1;
            helping_index_2 = character_index_1;
            break;
    }

    if((character_index_1 > 0 && map_layout[character_index_1] == ' ') &&     //collision checks
       (character_index_2 > 0 && map_layout[character_index_2] == ' ') &&
       (character_index_3 > 0 && map_layout[character_index_3] == ' ') &&
       (helping_index_1 > 0 && map_layout[helping_index_1] == ' ') &&
       (helping_index_2 > 0 && map_layout[helping_index_2] == ' '))
       {
        return false;
       }

    return true;
}

Tposition Tlevel::get_starting_position()
{
    return m_starting_position;
}

unsigned int Tlevel::get_current_map_height()
{
    return m_current_map_height;
}

unsigned int Tlevel::get_current_map_width()
{
    return m_current_map_width;
}

std::string Tlevel::get_current_map_layout()
{
    return m_map;
}

bool Tlevel::set_starting_position(Tposition p_position)
{
    m_starting_position = p_position;
    return true;
}