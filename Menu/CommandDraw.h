#ifndef COMMANDDRAW_H
#define COMMANDDRAW_H

#include "Command.h"
#include "Graph.h"
#include "GraphDrawer.h"
#include "Constants.h"

/**
 * @brief Command to draw the graph
*/
class CommandDraw : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandDraw();
        
        /**
         * Default destructor
         */
        virtual ~CommandDraw();

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
        virtual inline std::string CommandName() override { return "draw"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Draws the graph."; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "<width> <height> <draw_text> <file_path=output.svg>"; }

    protected:

    private:
};

#endif // COMMANDDRAW_H
