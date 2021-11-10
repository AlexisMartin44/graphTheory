#include "CommandReload.h"

#include "Menu.h"

CommandReload::CommandReload(std::map<std::string, std::pair<std::string, std::string>>& knownGraphs) : m_knownGraphs(knownGraphs)
{
    //ctor
}

CommandReload::~CommandReload()
{
    //dtor
}

void CommandReload::Execute(Graph& g)
{
    std::string path;
    std::string weightPath = "";
    if(std::cin.peek() == '\n')
    {
        path = g.GetTopologyPath();
        weightPath = g.GetWeightPath();
    }
    else
    {
        std::cin >> path;
        if(std::cin.peek() != '\n')
        {
            std::cin >> weightPath;
        }
        else
        {
            std::map<std::string, std::pair<std::string, std::string>>::iterator it = m_knownGraphs.find(path);
            if(it != m_knownGraphs.end())
            {
                path = it->second.first;
                weightPath = it->second.second;
            }
        }
    }
    g.Load(path, weightPath);
    std::cout << "Reloaded graph with topology '" << path << "'";
    if(weightPath != "")
    {
        std::cout << " and weights : '" << weightPath << "'";
    }
    std::cout << std::endl;
}

