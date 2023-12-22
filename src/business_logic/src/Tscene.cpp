#include "../include/Tscene.hpp"

Tscene::Tscene(unsigned int p_height, unsigned int p_width) : m_current_map_height(p_height), m_current_map_width(p_width)
{
    m_current_map_layout += std::string(m_current_map_width,'@') + '\n';
    for(unsigned int i = 0; i < m_current_map_height - 2; i++)
    {
        m_current_map_layout += '#' + std::string(m_current_map_width - 2,' ') + '#' + '\n';
    }
    m_current_map_layout += std::string(m_current_map_width,'#') + '\n';

    this -> add_floor();
}

bool Tscene::set_starting_position(Tposition p_position)
{
    m_starting_position = p_position;
    return true;
}

bool Tscene::is_next_pixel_wall(Ientity::Movement inputed_movement, Tposition p_position)
{
    auto player_position_1 = p_position;
    auto player_position_2 = p_position;
    auto player_position_3 = p_position;
    auto player_position_4 = p_position;
    auto player_position_5 = p_position;

    switch(inputed_movement)
    {
        case Ientity::Movement::Up:
            player_position_1.m_position_y -= 1;

            player_position_2.m_position_x += 1;
            player_position_2.m_position_y -= 2;

            player_position_3.m_position_x += 2;
            player_position_3.m_position_y -= 2;

            player_position_4.m_position_x += 3;
            player_position_4.m_position_y -= 2;

            player_position_5.m_position_x += 4;
            player_position_5.m_position_y -= 1;

            for(auto elem : m_platforms_container)
            {
                Tposition platform_position = elem.second.get_position();
                for(unsigned int i = 0; i < elem.second.get_width(); i++)
                {
                    if(player_position_1 == platform_position ||
                       player_position_2 == platform_position ||
                       player_position_3 == platform_position ||
                       player_position_4 == platform_position ||
                       player_position_5 == platform_position)
                       {
                            return true;
                       }
                       platform_position.m_position_x += 1;
                }
            }
            break;

        case Ientity::Movement::Down:
            player_position_1.m_position_y += 1;

            player_position_2.m_position_x += 1;
            player_position_2.m_position_y += 1;

            player_position_3.m_position_x += 2;
            player_position_3.m_position_y += 1;

            player_position_4.m_position_x += 3;
            player_position_4.m_position_y += 1;

            player_position_5.m_position_x += 4;
            player_position_5.m_position_y += 1;

            for(auto elem : m_platforms_container)
            {
                Tposition platform_position = elem.second.get_position();
                for(unsigned int i = 0; i < elem.second.get_width(); i++)
                {
                    if(player_position_1 == platform_position ||
                       player_position_2 == platform_position ||
                       player_position_3 == platform_position ||
                       player_position_4 == platform_position ||
                       player_position_5 == platform_position)
                       {
                            return true;
                       }
                       platform_position.m_position_x += 1;
                }
            }
            break;

        case Ientity::Movement::Left:
            player_position_1.m_position_x -= 1;
            player_position_2.m_position_y -= 1;

            for(auto elem : m_platforms_container)
            {
                Tposition platform_position = elem.second.get_position();
                for(unsigned int i = 0; i < elem.second.get_width(); i++)
                {
                    if(player_position_1 == platform_position ||
                       player_position_2 == platform_position)
                       {
                            return true;
                       }
                       platform_position.m_position_x += 1;
                }
            }
            break;

        case Ientity::Movement::Right:
        player_position_1.m_position_x += 5;

        player_position_2.m_position_y -= 1;
        player_position_2.m_position_x += 4;

        for(auto elem : m_platforms_container)
        {
            Tposition platform_position = elem.second.get_position();
            for(unsigned int i = 0; i < elem.second.get_width(); i++)
            {
                if(player_position_1 == platform_position ||
                    player_position_2 == platform_position)
                    {
                        return true;
                    }
                    platform_position.m_position_x += 1;
            }
        }
        break;
    }
    return false;
}

unsigned int Tscene::get_current_map_height()
{
    return m_current_map_height;
}

unsigned int Tscene::get_current_map_width()
{
    return m_current_map_width;
}

std::string Tscene::get_current_map_layout()
{
    return m_current_map_layout;
}

Tposition Tscene::get_starting_position()
{
    return m_starting_position;
}

Tposition Tscene::get_last_platform_position()
{
    return m_last_platform_position;
}

bool Tscene::set_last_platform_position(Tposition p_position)
{
    m_last_platform_position = p_position;
    return true;
}

bool Tscene::add_floor()
{
    Tposition floor_position(45,34);
    this -> set_last_platform_position(floor_position);
    this -> set_last_platform_width(50);
    m_platforms_container[0] = Tplatform(floor_position,1,50);
    return true;
}

bool Tscene::draw(WINDOW* gameplay_window)
{
    for(auto elem : m_platforms_container)
    {
        std::string platform_output(elem.second.get_width(),' ');
        mvwprintw(gameplay_window, elem.second.get_position().m_position_y - 1, elem.second.get_position().m_position_x, platform_output.c_str());
    }

    for(auto elem : m_platforms_container)
    {
        std::string platform_output(elem.second.get_width(),'@');
        mvwprintw(gameplay_window, elem.second.get_position().m_position_y, elem.second.get_position().m_position_x, platform_output.c_str());
    }

    return true;
}

bool Tscene::add_platform(Tplatform platform)
{
    static unsigned int platform_number = 1;
    m_platforms_container[platform_number] = platform;
    platform_number++;

    this -> set_last_platform_position(platform.get_position());
    m_last_platform_width = platform.get_width();
    return true;
}

bool Tscene::level_movement_down(WINDOW* gameplay_window)
{
    //unsigned short removing_objects_count = std::min(static_cast<short>(1), static_cast<short>(m_platforms_container.size()));
    //std::map<unsigned int, Tplatform>::iterator removing_iterator = m_platforms_container.begin();
    //std::advance(removing_iterator, removing_objects_count);
    unsigned int platform_key_to_remove = 9999;

    for(auto &elem : m_platforms_container)
    {
        elem.second.change_position(Tposition(elem.second.get_position().m_position_x, elem.second.get_position().m_position_y + 1));
        if(int(elem.second.get_position().m_position_y) >= this -> get_current_map_height() && elem.second.get_position().m_position_y > 0)
        {
            std::string platform_output(elem.second.get_width(),' ');
            mvwprintw(gameplay_window, elem.second.get_position().m_position_y - 1, elem.second.get_position().m_position_x, platform_output.c_str());
            platform_key_to_remove = elem.first;
        }
    }

    auto map_remove_iterator = m_platforms_container.find(platform_key_to_remove);
    if(map_remove_iterator != m_platforms_container.end())
    {
        m_platforms_container.erase(map_remove_iterator);
    }

    return true;
}

unsigned short Tscene::get_current_platforms_count()
{
    return m_platforms_container.size();
}

unsigned short Tscene::get_last_platform_width()
{
    return m_last_platform_width;
}

bool Tscene::set_last_platform_width(unsigned int p_width)
{
    this -> m_last_platform_width = p_width;
    return true;
}