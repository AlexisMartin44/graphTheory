#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <map>
#include <fstream>
#include <regex>

#include "Graph.h"
#include "Command.h"
#include "CommandReloadWeight.h"
#include "CommandCalculateIndice.h"
#include "CommandDraw.h"
#include "CommandDeletingEdges.h"
#include "CommandRestoreEdges.h"
#include "CommandComparaison.h"
#include "CommandReload.h"
#include "CommandDrawIndice.h"
#include "CommandInfos.h"
#include "CommandFlow.h"
#include "CommandKConnexity.h"
#include "CommandShortestPath.h"

/**
 * @brief Shows the user the possible commands
 */
class Menu
{
    public:
        /**
         * Default constructor
         */
        Menu();

        /**
         * Default destructor
         */
        virtual ~Menu();

        /**
         * Displays the menu
         */
        void Display();

    private:
        Graph m_graph; /** the Graph in question*/
        std::vector<Command*> m_commands; /** list of all the commands*/
        std::map<std::string, std::pair<std::string, std::string>> m_knownGraph; /** list of all the known Graph*/
};

#endif // MENU_H
