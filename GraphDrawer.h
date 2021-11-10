//
//  GraphDrawer.hpp
//  PiscineING2
//
//  Created by Titouan Lermite on 26/04/2020.
//  Copyright © 2020 Titouan Lermite. All rights reserved.
//

#ifndef GraphDrawer_hpp
#define GraphDrawer_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <limits>

#include "Graph.h"
#include "svgfile.h"
#include "IndicesWrapper.h"
#include "Constants.h"

/**
 * \brief Contains all functions related to the display
*/
class GraphDrawer
{
public:
    /**
     * Constructor
     * @param outputPath ame of the path to save the file
     * @param width width of the screen
     * @param height height of the screen
     */
    GraphDrawer(std::string outputPath = "output.svg", int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);

    /** Default destructor */
    ~GraphDrawer();

    /**
     * Draws all the nodes and all the edges
     *
     * @param g provides the nodes and the edges
     * @param draw_text draw the texts or not
     * @param adapt_size adapt the size of the Sommet or not
     */
    void Draw(Graph g, bool draw_text = true, bool adapt_size = false);

    /**
     * Draws all the nodes, all the edges and all the indices
     *
     * @param g provides the nodes and the edges
     * @param iw provides all the indices
     * @param draw_text draw the texts or not
     * @param adapt_size adapt the size of the Sommet or not
     */
    void Draw(Graph g, IndicesWrapper iw, bool draw_text = true, bool adapt_size = false);

     /**
      * Generates a color for each indice
      *
      * @return vector of colors in the rgb(r, g, b) format
      * @param iw indices to base the colors on
     */
    std::vector<std::string> Colors(IndicesWrapper iw);

    /**
     * Generates a multiplication coefficient for each indice
     *
     * @return vector of multiplicator coefficients
     * @param iw indices to base the coefficients on
    */
    std::vector<double> AdaptRadius(IndicesWrapper iw);

    /**
     * Draws the shortest way to go from a Sommet A to a Sommet B
     *
     * @param g the graph
     * @param aretesVertes ids of the Arete to go through
    */
    void DrawShortestPath(Graph g, std::set<int> aretesVertes);

    /**
     * Calculates the distance between the two nearest points
     * Algorithms found here https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
     *
     * @return the maximum radius so that 2 Sommet do not touch each other
     * @param points all the Sommet
     */
    double Closest(std::vector<Sommet> points);

    /**
     * Calculates the distance between the two nearest points in a sorted vector
     *
     * @return the maximum radius
     * @param points all the Sommet
     */
    double ClosestSorted(std::vector<Sommet> points);

    /**
     * Calculates the distance between the two nearest points using brute force
     *
     * @return the maximum radius
     * @param points all the Sommet
     */
    double BruteForce(std::vector<Sommet> points);

    /**
     * Calculates the distance between two Sommet
     *
     * @return the maximum radius so that 2 Sommet do not touch each other
     * @param a Sommet a
     * @param b Smomet b
     */
    double Distance(Sommet a, Sommet b);

    /**
     * Determines the lowest radius between two radiuses
     *
     * @return the lowest radius
     * @param left radius one
     * @param right radius two
     */
    double Min(double left, double right);

    /**
     * Determines the lowest radius
     *
     * @return the lowest radius
     * @param strip vector of Sommet close to the delimination
     * @param dist the actual lowest radius
     */
    double ClosestStrip(std::vector<Sommet> strip, double dist);

private:
    std::string m_outputPath; /**name of the path to save the file*/
    double m_rayon; /**radius of the Sommet*/
    int m_width, m_height; /**width et height of the screen*/
};

#endif /* GraphDrawer_hpp */
