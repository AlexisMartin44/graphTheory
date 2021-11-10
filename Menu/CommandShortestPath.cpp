#include "CommandShortestPath.h"

CommandShortestPath::CommandShortestPath()
{
    //ctor
}

CommandShortestPath::~CommandShortestPath()
{
    //dtor
}

void CommandShortestPath::Execute(Graph& g)
{
    int temp;
    std::vector<int> departArrivee;

    if(std::cin.peek() == '\n')
    {
        std::cout << "Please indicate the starting vertex then the finishing vertex [0:" << g.GetSommets().size() - 1 << "] : ";
    }
    do
    {
        std::cin >> temp;
        departArrivee.push_back(temp);
    }while(std::cin.peek()!='\n');

    g.Dijkstra(departArrivee[0], departArrivee[1]);
}
