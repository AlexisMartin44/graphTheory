#ifndef COMMANDINFOS_H
#define COMMANDINFOS_H

#include "Command.h"

#include "Graph.h"

/**
 * @brief Command to display the informations of the Graph
*/
class CommandInfos : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandInfos();
        
        /**
         * Default destructor
         */
        virtual ~CommandInfos();

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
        virtual inline std::string CommandName() override { return "infos"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Displays the infos of the graph"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return ""; }

    protected:

    private:
};

#endif // COMMANDINFOS_H
