#include "CommandFlow.h"

CommandFlow::CommandFlow()
{
    //ctor
}

CommandFlow::~CommandFlow()
{
    //dtor
}

void CommandFlow::Execute(Graph& g)
{
    int from, towards;
    if(std::cin.peek() == '\n')
    {
        std::cout << "Please enter the beginning and ending vertexes ids : ";
    }
    std::cin >> from >> towards;
    GraphFlow gf(g);
    std::cout << "The maximum flow from " << from << " to " << towards << " is " << gf.Flow(from, towards) << std::endl;
}
