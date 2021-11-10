#include "CommandInfos.h"

CommandInfos::CommandInfos()
{
    //ctor
}

CommandInfos::~CommandInfos()
{
    //dtor
}

void CommandInfos::Execute(Graph& g)
{
    std::cout << g;
}
