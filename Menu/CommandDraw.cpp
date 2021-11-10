#include "CommandDraw.h"

CommandDraw::CommandDraw()
{
    //ctor
}

CommandDraw::~CommandDraw()
{
    //dtor
}

void CommandDraw::Execute(Graph& g)
{
    std::string path = "output.svg";
    int width = SCREEN_WIDTH, height = SCREEN_HEIGHT;
    bool draw_text = true;
    if(std::cin.peek() == '\n')
    {
        width = SCREEN_WIDTH;
    }
    else
    {
        std::cin >> width;
        if(std::cin.peek() == '\n')
        {
            height = SCREEN_HEIGHT;
        }
        else
        {
            std::cin >> height;
            if(std::cin.peek() == '\n')
            {
                draw_text = true;
            }
            else
            {
                std::string s;
                std::cin >> s;
                draw_text = s[0] == 'y';
                if(std::cin.peek() == '\n')
                {
                    path = "output.svg";
                }
                else
                {
                    std::cin >> path;
                }
            }
        }
    }

    GraphDrawer gd(path, width, height);
    gd.Draw(g, draw_text);
}
