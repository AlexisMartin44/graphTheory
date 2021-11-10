#include "Menu.h"

Menu::Menu()
{
    std::ifstream f("knownGraphs.txt");
    if(f.is_open())
    {
        const std::regex lineRegex("^((?:\"[^\"]*\")|[^\"\\s]+)\\s((?:\"[^\"]*\")|[^\"\\s]+)(?:\\s((?:\"[^\"]*\")|[^\"\\s]+))?$");
        while(!f.eof())
        {
            std::string line;
            std::getline(f, line);
            std::smatch match;
            if(std::regex_match(line, match, lineRegex))
            {
                if(match.size() >= 3)
                {
                    m_knownGraph.insert({match[1].str(), {match[2].str(), match.size() > 3 ? match[3].str() : ""}});
                }
            }
        }
    }
    m_commands.push_back(new CommandCalculateIndice());
    m_commands.push_back(new CommandComparaison());
    m_commands.push_back(new CommandDraw());
    m_commands.push_back(new CommandDrawIndice());
    m_commands.push_back(new CommandDeletingEdges());
    m_commands.push_back(new CommandFlow());
    m_commands.push_back(new CommandInfos());
    m_commands.push_back(new CommandReload(m_knownGraph));
    m_commands.push_back(new CommandReloadWeight());
    m_commands.push_back(new CommandRestoreEdges());
    m_commands.push_back(new CommandKConnexity());
    m_commands.push_back(new CommandShortestPath());
}

Menu::~Menu()
{
    for(auto& it : m_commands)
    {
        delete it;
    }
}

void Menu::Display()
{
    std::cout << "Please enter a known topology name or a file path to load or ? to display the known graphs : ";
    bool loaded = false;
    while(!loaded)
    {
        std::string name;
        std::getline(std::cin, name);
        if(name == "?")
        {
            for(auto& it : m_knownGraph)
            {
                std::cout << it.first << " : " << it.second.first << "\t" << it.second.second << std::endl;
            }
            std::cout << "Please make your choice : ";
        }
        else
        {
            std::map<std::string, std::pair<std::string, std::string>>::iterator it = m_knownGraph.find(name);
            if(it != m_knownGraph.end())
            {
                m_graph.Load(it->second.first, it->second.second);
                std::cout << "Loaded graph " << name << std::endl;
            }
            else
            {
                m_graph.LoadTopology(name);
                std::cout << "Enter a weight file or press enter to skip : ";
                std::getline(std::cin, name);
                if(name != "")
                {
                    m_graph.LoadWeights(name);
                }
            }
            loaded = true;
        }
    }

    std::string command;
    do
    {
        std::cout << "Please enter a command or help|? : ";
        std::cin >> command;
        if(command == "help" || command == "?")
        {
            std::cout << std::endl << "\texit\tExits the program" << std::endl << std::endl;
            for(auto& it : m_commands)
            {
                std::cout << "\t" << it->CommandName() << "\t" << it->CommandDescription() << std::endl;
                if(it->CommandUsage() != "")
                {
                    std::cout << std::endl << "\t\tUsage: " << it->CommandName() << " " << it->CommandUsage() << std::endl;
                }
                std::cout << std::endl;
            }
        }
        else
        {
            for(auto& it : m_commands)
            {
                if(it->CommandName() == command)
                {
                    it->Execute(m_graph);
                }
            }
        }
    }
    while(command != "exit");
}
