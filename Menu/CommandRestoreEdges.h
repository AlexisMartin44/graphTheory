#ifndef COMMANDRESTOREEDGES_H_INCLUDED
#define COMMANDRESTOREEDGES_H_INCLUDED

#include <stdio.h>
#include <string>
#include <iostream>

#include "Command.h"
#include "GraphIndices.h"
#include "IndicesWrapper.h"

/**
 * @brief Command to restore some Arete
*/
class CommandRestoreEdges : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandRestoreEdges();

        /**
         * Default destructor
         */
        virtual ~CommandRestoreEdges();

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
        virtual inline std::string CommandName() override { return "restore-edges"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Allows to restore an edge"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[edges ids...]"; }

};


#endif // COMMANDRESTOREEDGES_H_INCLUDED
