#pragma once

#include <curses.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

//Library definitions
#include "../business_logic/include/Tplayer.hpp"
#include "Idrawable.hpp"
#include "drawable_player.hpp"

//Global game loop functions

bool input_processing(const std::shared_ptr<Ientity>& player);
WINDOW* initial_window_gameplay_output();
WINDOW* initial_window_scoreboard_output();
bool gameloop();
void update(WINDOW* win, std::shared_ptr<drawable_player> player);
