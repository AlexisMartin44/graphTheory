#ifndef COMMANDDELETINGEDGES_H_INCLUDED
#define COMMANDDELETINGEDGES_H_INCLUDED

#include <stdio.h>
#include <string>
#include <iostream>

#include "Command.h"
#include "GraphIndices.h"

/**
 * @brief Command to delete some Arete
*/
class CommandDeletingEdges : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandDeletingEdges();

        /**
         * Default destructor
         */
        virtual ~CommandDeletingEdges();

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
        virtual inline std::string CommandName() override { return "remove-edges"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Allows to delete one or multiple edges"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[edges ids...]"; }

};

#endif // COMMANDDELETINGEDGES_H_INCLUDED
