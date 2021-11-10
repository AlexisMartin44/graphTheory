//
//  CommandDrawIndice.cpp
//  PiscineING2
//
//  Created by Titouan Lermite on 28/04/2020.
//  Copyright © 2020 Titouan Lermite. All rights reserved.
//

#include "CommandDrawIndice.h"

CommandDrawIndice::CommandDrawIndice()
{
    //ctor
}

CommandDrawIndice::~CommandDrawIndice()
{
    //dtor
}

void CommandDrawIndice::Execute(Graph& g)
{
    char mask = 0b0000;
    if(std::cin.peek() == '\n')
    {
        std::cout << "Please indicate which indices you want to draw " << CommandUsage() << ": ";
    }
    int width = SCREEN_WIDTH, height = SCREEN_HEIGHT;
    std::string path = "output.svg";
    std::string str;
    std::cin >> str;
    bool draw_text = true;
    if (str == "degree")
        mask = DEGREE;
    else if (str == "proximity")
        mask = PROXIMITY;
    else if (str == "vecteur-propre")
        mask = VECT_PROPRE;
    else if (str == "betweenness")
        mask = BETWEENNESS;
    else if (str == "all")
        mask = -1;
    if(std::cin.peek() == '\n')
    {
        width = SCREEN_WIDTH;
    }
    else
    {
        std::cin >> width;
        if(std::cin.peek() == '\n')
        {
            height = SCREEN_HEIGHT;
        }
        else
        {
            std::cin >> height;
            if(std::cin.peek() == '\n')
            {
                draw_text = true;
            }
            else
            {
                std::string s;
                std::cin >> s;
                draw_text = s[0] == 'y';
                if(std::cin.peek() == '\n')
                {
                    path = "output.svg";
                }
                else
                {
                    std::cin >> path;
                }
            }
        }
    }
    bool size_node = false;
    std::cout << "Do you want to adapt the radius of the nodes according to their index (y|n) : ";
    std::string s;
    std::cin >> s;
    size_node = s[0] == 'y';
    GraphIndices gi(g);
    GraphDrawer gd(path, width, height);
    std::vector<IndicesWrapper> viw(4);
    if((mask & DEGREE) != 0)
    {
        viw[0] = gi.CentraliteDegre();
        GraphDrawer deg("output_degree.svg", width, height);
        deg.Draw(g, viw[0], draw_text, size_node);
        if(mask != -1)
        {
            gd.Draw(g, viw[0], draw_text, size_node);
        }
        std::cout << "Degree centrality calculated" << std::endl;
    }
    if((mask & PROXIMITY) != 0)
    {
        viw[1] = gi.CentraliteProximite();
        GraphDrawer prox("output_proximity.svg", width, height);
        prox.Draw(g, viw[1], draw_text, size_node);
        if(mask != -1)
        {
            gd.Draw(g, viw[1], draw_text, size_node);
        }
        std::cout << "Proximity centrality calculated" << std::endl;
    }
    if((mask & VECT_PROPRE) != 0)
    {
        viw[2] = gi.CentraliteVecteurPropre();
        GraphDrawer vec("output_vector.svg", width, height);
        vec.Draw(g, viw[2], draw_text, size_node);
        if(mask != -1)
        {
            gd.Draw(g, viw[2], draw_text, size_node);
        }
        std::cout << "Eigen vector centrality calculated" << std::endl;
    }
    if((mask & BETWEENNESS) != 0)
    {
        viw[3] = gi.CentraliteBetweenness();
        GraphDrawer bet("output_betweenness.svg", width, height);
        bet.Draw(g, viw[3], draw_text, size_node);
        if(mask != -1)
        {
            gd.Draw(g, viw[3], draw_text, size_node);
        }
        std::cout << "Betweenness centrality calculated" << std::endl;
    }
    if(mask == -1)
    {
        IndicesWrapper iw = gi.AverageCentralites(viw);
        gd.Draw(g, iw, draw_text, size_node);
    }
}
