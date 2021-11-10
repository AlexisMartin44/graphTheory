#ifndef COMMANDSHORTESTPATH_H_INCLUDED
#define COMMANDSHORTESTPATH_H_INCLUDED

#include <stdio.h>
#include <string>
#include <iostream>

#include "Command.h"
#include "GraphIndices.h"

/**
 * @brief Command to display the shortest path from one Sommet to another
*/
class CommandShortestPath : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandShortestPath();

        /**
         * Default destructor
         */
        virtual ~CommandShortestPath();

        /**
         * Command call
         *
         * @param g the graph in question
         */
        virtual void Execute(Graph& g) override;

        /**
         * Command text
         *
         * @return name of the command
         */
        virtual inline std::string CommandName() override { return "shortest-path"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Displays the shortest path from A to B"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[vertices ids...]"; }
};

#endif // COMMANDSHORTESTPATH_H_INCLUDED
