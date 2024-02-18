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
#include <stdlib.h>
#include <vector>

//Library definitions
#include "Tplayer.hpp"
#include "Idrawable.hpp"
#include "drawable_player.hpp"
#include "Tlevel.hpp"
#include "Tplatform.hpp"
#include "Tscene.hpp"

//Global game loop functions


std::unique_ptr<WINDOW, std::function<void(WINDOW*)>> initial_window_gameplay_output(
    std::shared_ptr<Ilevel> p_current_level, unsigned int height, unsigned int width);

inline auto WINDOW_deleter = [](WINDOW* win) { delwin(win); };
std::unique_ptr<WINDOW, decltype(WINDOW_deleter)> initial_window_scoreboard_output();

bool input_processing(const std::shared_ptr<Ientity>& player);
bool gameloop();
bool update(WINDOW* const win, WINDOW* const win_score, std::shared_ptr<drawable_player> player, std::shared_ptr<Tscene> current_level);
std::tuple<std::string, unsigned int, unsigned int> map_converter(std::string file_name);
bool border_refresh(WINDOW* gameplay_window, std::shared_ptr<Tscene> current_level);
bool starting_screen();
bool ending_screen();
std::vector<std::string> fill_palette();
void generate_frame(std::string* content, std::vector<std::string>* palette, unsigned int step, unsigned int height, unsigned int width);
void screen_refresh(std::string* content);
