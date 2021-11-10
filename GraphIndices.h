#ifndef GRAPHINDICES_H
#define GRAPHINDICES_H

#include <queue>
#include <vector>
#include <cmath>
#include <stack>
#include <list>

#include "Graph.h"
#include "IndicesWrapper.h"
#include "Constants.h"
#include <queue>
#include <stack>

/**
 * \brief Contains all the functions regarding the calculations of the indices : the normal ones and the normalized ones
*/
class GraphIndices
{
    public:
        /**
         * Default constructor
         */
        GraphIndices(const Graph& graph);
        
        /**
         * Default destructor
         */
        ~GraphIndices();
        
        /**
         * Calculates the normal and normalized indices for degree centrality
         * Complexity: O(A * S), S being the Order and A the size
         *
         * @return IndicesWrapper containing the indices
         */
        IndicesWrapper CentraliteDegre();
        
        /**
         * Calculates the normal and normalized indices for eigenvector centrality
         * Complexity: O(n * S * (2 + A)), n being the number of epoch required to stabilize lambda, S the Order and A the size
         *
         * @return IndicesWrapper containing the indices
        */
        IndicesWrapper CentraliteVecteurPropre();
        
        /**
         * Calculates the normal and normalized indices for proximity centrality
         * Complexity: O(A * S + S^2 * log(S)), S being the Order and A the size
         *
         * @return IndicesWrapper containing the indices
         */
        IndicesWrapper CentraliteProximite();

        /**
         * Brands algorithm found here : https://www.eecs.wsu.edu/~assefaw/CptS580-06/papers/brandes01centrality.pdf
         * and re-adapted to support weights
         * Complexity: O(S * (S * (A + n) + 1)), S being the Order, A the size and n the count of shortest paths
         *
         * @return IndicesWrapper containing the indices
         */
        IndicesWrapper CentraliteBetweenness();
    
        /**
         * Calculates the average of all indices for each Sommet
         *
         * @return IndicesWrapper containing the indices
         * @param viw vector of IndicesWrapper containing all the indices
         */
        IndicesWrapper AverageCentralites(std::vector<IndicesWrapper> viw);

        /**
         * Calculates all the distances using Dijkstra algorithm
         *
         * @param firstPoint start of the path
         * @param iw stocks the values
         */
        void Dijkstra(unsigned firstPoint, IndicesWrapper& iw);
        
        void afficherChemin(std::vector<int> predecesseur, int num);
        void IndexCalculation(std::vector<int> predecesseur, int num, int& shortestPath);
    private:
        const Graph& m_graph; /** contains a Graph and all his informations */
};

#endif // GRAPHINDICES_H
