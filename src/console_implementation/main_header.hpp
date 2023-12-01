#pragma once

#include <curses.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

//Library definitions
#include "../business_logic/include/Tplayer.hpp"
#include "../business_logic/include/Idrawable.hpp"
#include "player_drawing_module.hpp"

//Global game loop functions

bool input_processing(const std::shared_ptr<Ientity>& player);
WINDOW* window_gameplay_output();
WINDOW* window_scoreboard_output();
bool gameloop();
