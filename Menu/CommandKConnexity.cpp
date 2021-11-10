#include "CommandKConnexity.h"

CommandKConnexity::CommandKConnexity()
{
    //ctor
}

CommandKConnexity::~CommandKConnexity()
{
    //dtor
}

void CommandKConnexity::Execute(Graph& g)
{
    int k = g.KConnectivity();
    std::cout << "The current graph is " << k << "-edges-connected.\n" << std::endl;
}
