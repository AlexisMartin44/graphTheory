#ifndef COMMAND_H
#define COMMAND_H

#include "Graph.h"

/**
 * @brief Virtual class used for each command
 */
class Command
{
    public:
        /**
         * Default constructor
         */
        Command();
        
        /**
         * Default destructor
         */
        virtual ~Command();

        /**
         * Command call
         *
         * @param g the graph in question
         */
        virtual void Execute(Graph& g) = 0;

        /**
         * Command text
         */
        inline virtual std::string CommandName() = 0;

        /**
         * Command description
         */
        inline virtual std::string CommandDescription() = 0;

        /**
         * Command usage
         */
        inline virtual std::string CommandUsage() { return ""; }
};

#endif // COMMAND_H
