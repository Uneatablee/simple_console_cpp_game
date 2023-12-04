#pragma once

#include <curses.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>

//Library definitions
#include "Tplayer.hpp"
#include "Idrawable.hpp"
#include "drawable_player.hpp"
#include "Tlevel.hpp"

//Global game loop functions

bool input_processing(const std::shared_ptr<Ientity>& player);
WINDOW* initial_window_gameplay_output(std::shared_ptr<Ilevel> p_current_level, unsigned int height, unsigned int width);
WINDOW* initial_window_scoreboard_output();
bool gameloop();
void update(WINDOW* win, std::shared_ptr<drawable_player> player);
std::string map_converter(std::string file_name, unsigned int* map_height, unsigned int* map_width);
