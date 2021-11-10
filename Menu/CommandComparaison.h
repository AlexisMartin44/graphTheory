#ifndef COMMANDCOMPARAISON_H_INCLUDED
#define COMMANDCOMPARAISON_H_INCLUDED

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "Command.h"
#include "GraphIndices.h"
#include "IndicesWrapper.h"

/**
 * @brief Command to compare the latest index results with the previous ones
*/
class CommandComparaison : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandComparaison();
        
        /**
         * Default destructor
         */
        virtual ~CommandComparaison();

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
        virtual inline std::string CommandName() override { return "comparaison"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Compare the latest index results with the previous ones"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return ""; }

    protected:
    private:

};

#endif // COMMANDCOMPARAISON_H_INCLUDED
