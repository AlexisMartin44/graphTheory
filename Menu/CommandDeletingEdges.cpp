#include "CommandDeletingEdges.h"

CommandDeletingEdges::CommandDeletingEdges()
{
    //ctor
}

CommandDeletingEdges::~CommandDeletingEdges()
{
    //dtor
}

void CommandDeletingEdges::Execute(Graph& g)
{
    int suppr;

    if(std::cin.peek() == '\n')
    {
        std::cout << "Please indicate which edge you want to delete by entering its id [0:" << g.GetAretes().size() - 1 << "] : ";
    }
    do
    {
        std::cin >> suppr;
        g.GetDeleted().insert(suppr);
    }while(std::cin.peek()!='\n');

    if(g.IsConnexe())
    {
        if(g.IsStronglyConnexe())
            std::cout << "After deletion, the graph remains strongly-connected." << std::endl;
        else
            std::cout << "After deletion, the graph is connected but not strongly-connected." << std::endl;
    }
    else
        std::cout << "After deletion, the graph is no longer connected." << std::endl;
}
