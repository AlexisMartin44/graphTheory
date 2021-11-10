#include "CommandReloadWeight.h"

CommandReloadWeight::CommandReloadWeight()
{
    //ctor
}

CommandReloadWeight::~CommandReloadWeight()
{
    //dtor
}

void CommandReloadWeight::Execute(Graph& g)
{
    std::string path;
    if(std::cin.peek() == '\n')
    {
        std::cout << "Please enter the new weights file : ";
    }
    std::cin >> path;
    g.LoadWeights(path);
}

