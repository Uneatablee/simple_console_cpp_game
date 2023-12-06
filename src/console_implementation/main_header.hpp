#pragma once

#include <curses.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>

//Library definitions
#include "Tplayer.hpp"
#include "Idrawable.hpp"
#include "drawable_player.hpp"
#include "Tlevel.hpp"

//Global game loop functions


std::unique_ptr<WINDOW, std::function<void(WINDOW*)>> initial_window_gameplay_output(
    std::shared_ptr<Ilevel> p_current_level, unsigned int height, unsigned int width);

inline auto WINDOW_deleter = [](WINDOW* win) { delwin(win); };
std::unique_ptr<WINDOW, decltype(WINDOW_deleter)> initial_window_scoreboard_output();

bool input_processing(const std::shared_ptr<Ientity>& player);
bool gameloop();
void update(WINDOW* const win, std::shared_ptr<drawable_player> player);
std::tuple<std::string, unsigned int, unsigned int> map_converter(std::string file_name);
