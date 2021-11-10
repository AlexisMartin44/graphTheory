#ifndef COMMANDKCONNEXITY_H_INCLUDED
#define COMMANDKCONNEXITY_H_INCLUDED

#include <stdio.h>
#include <string>
#include <iostream>

#include "Command.h"
#include "GraphIndices.h"

/**
 * @brief Command to calculate the k-connectivity
*/
class CommandKConnexity : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandKConnexity();

        /**
         * Default destructor
         */
        virtual ~CommandKConnexity();

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
        virtual inline std::string CommandName() override { return "k-connexity"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Calculates k-connectivity"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return ""; }

};


#endif // COMMANDKCONNEXITY_H_INCLUDED
