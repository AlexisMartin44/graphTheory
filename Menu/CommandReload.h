#ifndef COMMANDRELOAD_H
#define COMMANDRELOAD_H

#include <map>
#include <string>
#include <utility>

#include "Command.h"

class Menu;

/**
 * @brief Command to reload a Graph
*/
class CommandReload : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandReload(std::map<std::string, std::pair<std::string, std::string>>& knownGraphs);

        /**
         * Default destructor
         */
        virtual ~CommandReload();

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
        virtual inline std::string CommandName() override { return "reload"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Reloads the current graph, or reloads another graph"; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[topology_file_path] [weights_file_path]"; }

    private:
        std::map<std::string, std::pair<std::string, std::string>>& m_knownGraphs; /** list of all the known Graphs*/
};

#endif // COMMANDRELOAD_H
