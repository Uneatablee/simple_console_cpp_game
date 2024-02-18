#include "main_header.hpp"

using namespace std;

struct Colour
{
    Colour(unsigned int r, unsigned int g,unsigned int b) : red(r), green(g), blue(b)
    {
        colour_content = "\x1b[48;2;" +to_string(red) + ";" + to_string(green) + ";" + to_string(blue) + "m" +"   " + "\x1b[0m";
    }

    string colour_content;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

};

void generate_frame(string* content, vector<string>* colour, unsigned int step, unsigned int hei = 10, unsigned int wei = 10)
{
    unsigned int height = hei;
    unsigned int width = wei;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if((j > 8 && j < 15 && i == 10) ||
            (j > 7 && j < 10 && i == 11) ||
            (j > 7 && j < 10 && i == 12) ||
            (j > 7 && j < 10 && i == 13) ||
            (j > 8 && j < 15 && i == 14) ||
            (j > 14 && j < 16 && i == 13) ||
            (j > 13 && j < 16 && i == 12) ||

            (j > 17 && j < 23 && i == 10) ||
            (j > 16 && j < 19 && i == 11) ||
            (j > 16 && j < 24 && i == 12) ||
            (j > 16 && j < 19 && i == 13) ||
            (j > 16 && j < 19 && i == 14) ||
            (j > 21 && j < 24 && i == 11) ||
            (j > 21 && j < 24 && i == 13) ||
            (j > 21 && j < 24 && i == 14) ||

            (j > 24 && j < 28 && i == 10) ||
            (j > 24 && j < 29 && i == 11) ||
            (j > 24 && j < 27 && i == 12) ||
            (j > 24 && j < 27 && i == 13) ||
            (j > 24 && j < 27 && i == 14) ||
            (j > 27 && j < 32 && i == 12) ||
            (j > 32 && j < 35 && i == 12) ||
            (j > 31 && j < 35 && i == 10) ||
            (j > 30 && j < 35 && i == 11) ||
            (j > 28 && j < 31 && i == 13) ||
            (j > 32 && j < 35 && i == 14) ||
            (j > 32 && j < 35 && i == 13) ||

            (j > 35 && j < 43 && i == 10) ||
            (j > 35 && j < 38 && i == 11) ||
            (j > 35 && j < 41 && i == 12) ||
            (j > 35 && j < 38 && i == 13) ||
            (j > 35 && j < 43 && i == 14) ||


            (j > 8 && j < 15 && i == 17) ||
            (j > 7 && j < 10 && i == 18) ||
            (j > 7 && j < 10 && i == 19) ||
            (j > 7 && j < 10 && i == 20) ||
            (j > 8 && j < 15 && i == 21) ||
            (j > 13 && j < 16 && i == 18) ||
            (j > 13 && j < 16 && i == 19) ||
            (j > 13 && j < 16 && i == 20) ||

            (j > 16 && j < 19 && i == 17) ||
            (j > 16 && j < 19 && i == 18) ||
            (j > 16 && j < 19 && i == 19) ||
            (j > 17 && j < 20 && i == 20) ||
            (j > 18 && j < 23 && i == 21) ||
            (j > 22 && j < 25 && i == 17) ||
            (j > 22 && j < 25 && i == 18) ||
            (j > 22 && j < 25 && i == 19) ||
            (j > 21 && j < 24 && i == 20) ||

            (j > 25 && j < 33 && i == 17) ||
            (j > 25 && j < 28 && i == 18) ||
            (j > 25 && j < 31 && i == 19) ||
            (j > 25 && j < 28 && i == 20) ||
            (j > 25 && j < 33 && i == 21) ||

            (j > 33 && j < 40 && i == 17) ||
            (j > 33 && j < 36 && i == 18) ||
            (j > 33 && j < 40 && i == 19) ||
            (j > 33 && j < 36 && i == 20) ||
            (j > 33 && j < 36 && i == 21) ||
            (j > 38 && j < 41 && i == 18) ||
            (j > 38 && j < 41 && i == 20) ||
            (j > 38 && j < 41 && i == 21))
            {
                *content += Colour(j + i* 4.5,j*4.5 / i,j*4.5).colour_content;
            }
            else
            {
                *content += (*colour)[j + step];
            }
        }
        *content += "\n";
    }
}

vector<string> fill_palette()
{
    vector<string> palette;

    for(int i = 0; i < 255; i++)
    {
        palette.push_back(Colour(255, 0, i).colour_content);
    }

    return palette;
}


void sleep(int number)
{
    int a = 0;
    for(int i = 0; i<number; i++) a++;
}

void screen_refresh(string* content)
{
    cout << *content << flush;
    sleep(6000000);
    *content = "";
    system("clear");
}


//  ██████   █████  ███    ███ ███████
// ██       ██   ██ ████  ████ ██
// ██   ███ ███████ ██ ████ ██ █████
// ██    ██ ██   ██ ██  ██  ██ ██
//  ██████  ██   ██ ██      ██ ███████


//  ██████  ██    ██ ███████ ██████
// ██    ██ ██    ██ ██      ██   ██
// ██    ██ ██    ██ █████   ██████
// ██    ██  ██  ██  ██      ██   ██
//  ██████    ████   ███████ ██   ██

