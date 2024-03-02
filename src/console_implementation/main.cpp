#include "main_header.hpp"

bool game_over = false;
bool alive_input = false;

int main()
{
    {
    const auto standard_screen = std::unique_ptr<WINDOW, void (*)(WINDOW*)>(
        initscr(),
        [](WINDOW*)
        {
            endwin();
        });

    cbreak();
    keypad(standard_screen.get(), TRUE); // https://invisible-island.net/ncurses/ncurses-intro.html
    noecho();

    gameloop(); //--> gameloop with gameplaywindow and player

    {
        std::cout << std::endl;
    }
    //INCLUDE TO STARTING SCREEN -> red curtains so that game uses ansii colours also.
    }


    std::string content = "";
    std::vector<std::string> colours_palette = fill_palette();

    unsigned int height = 40;
    unsigned int width = 47;


    for(int i = 0; i < 5; i++)
    {
        for(int step = 0; step < 100; step++)
        {
            generate_frame(&content, &colours_palette, step, height, width);
            screen_refresh(&content);
        }
    }

}
