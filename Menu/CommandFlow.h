#ifndef COMMANDFLOW_H
#define COMMANDFLOW_H

#include "Command.h"

#include "Graph.h"
#include "CommandFlow.h"

/**
 * @brief Command to calculate the flow between to Sommet
*/
class CommandFlow : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandFlow();
        
        /**
         * Default destructor
         */
        virtual ~CommandFlow();

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
        virtual inline std::string CommandName() override { return "flow"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Calculates the flow between two vertexes"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "<from> <towards>"; }

    protected:

    private:
};

#endif // COMMANDFLOW_H
