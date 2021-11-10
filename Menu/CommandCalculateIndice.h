#ifndef COMMANDCALCULATEINDICE_H
#define COMMANDCALCULATEINDICE_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "Command.h"
#include "GraphIndices.h"
#include "IndicesWrapper.h"
#include "Constants.h"

/**
 * @brief Command to calculate the indices
 */
class CommandCalculateIndice : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandCalculateIndice();
        
        /**
         * Default destructor
         */
        virtual ~CommandCalculateIndice();

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
        virtual inline std::string CommandName() override { return "indices"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Calculates the requested indice."; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[degree|vecteur-propre|proximity|betweenness|all]"; }

    protected:

    private:
};

#endif // COMMANDCALCULATEINDICE_H
