#include "CommandRestoreEdges.h"

CommandRestoreEdges::CommandRestoreEdges()
{
    //ctor
}

CommandRestoreEdges::~CommandRestoreEdges()
{
    //dtor
}

void CommandRestoreEdges::Execute(Graph& g)
{
    int restore;
    std::set<int>::iterator it;

    if(std::cin.peek() == '\n')
    {
        std::cout << "Please indicate which edge you want to restore by entering its id [0:" << g.GetConstAretes().size() - 1 << "] : ";
    }
    do
    {
        std::cin >> restore;
        it = g.GetDeleted().begin();
        g.GetDeleted().erase(it, g.GetDeleted().end());
    }while(std::cin.peek()!='\n');

}
