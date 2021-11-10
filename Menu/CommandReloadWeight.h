#ifndef COMMANDRELOADWEIGHT_H
#define COMMANDRELOADWEIGHT_H

#include "Command.h"

/**
 * @brief Command to reload the weights
*/
class CommandReloadWeight : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandReloadWeight();

        /**
         * Default destructor
         */
        virtual ~CommandReloadWeight();

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
        virtual inline std::string CommandName() override { return "reload-weights"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Reloads the weights with the provided path."; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "<weights_file_path>"; }

    protected:

    private:
};

#endif // COMMANDRELOADWEIGHT_H
