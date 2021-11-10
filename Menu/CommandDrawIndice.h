//
//  CommandDrawIndice.hpp
//  PiscineING2
//
//  Created by Titouan Lermite on 28/04/2020.
//  Copyright © 2020 Titouan Lermite. All rights reserved.
//

#ifndef CommandDrawIndice_hpp
#define CommandDrawIndice_hpp

#include <stdio.h>
#include <string>
#include <iostream>

#include "Command.h"
#include "GraphIndices.h"
#include "IndicesWrapper.h"
#include "GraphDrawer.h"
#include "Constants.h"

/**
 * @brief Command to draw the indices
*/
class CommandDrawIndice : public Command
{
    public:
        /**
         * Default constructor
         */
        CommandDrawIndice();
        
        /**
         * Default destructor
         */
        virtual ~CommandDrawIndice();

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
        virtual inline std::string CommandName() override { return "draw-indices"; }

        /**
         * Command description
         *
         * @return what the command does
         */
        virtual inline std::string CommandDescription() override { return "Draws the requested indice."; }

        /**
         * Command usage
         *
         * @return how the command works
         */
        virtual inline std::string CommandUsage() override { return "[degree|vecteur-propre|proximity|betweenness|all] <width> <height> <draw_text> <file_path=output.svg>"; }
    protected:

    private:
};

#endif /* CommandDrawIndice_hpp */
