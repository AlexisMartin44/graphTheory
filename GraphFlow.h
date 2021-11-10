#ifndef GRAPHFLOTS_H
#define GRAPHFLOTS_H

#include <vector>
#include <queue>

class Graph;

/**
 * \brief Contains all informations about the maximum flow from a Sommet to another
*/
class GraphFlow
{
    public:
        /**
         * Default constructor
         */
        GraphFlow(const Graph& g, bool useWeights = true);
        
        /**
         * Default destructor
         */
        virtual ~GraphFlow();

        /**
         * Calculates the flow from Sommet source to Sommet sink
         * This is done using the Edmonds-Karp algorithm, an adaptation of the Ford Fulkerson's one
         * The pseudocode used can be found here : https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm and
         * https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
         *
         * @return the maximum flow
         * @param source start of the path
         * @param sink end of the path
        */
        double Flow(int source, int sink);

        /**
         * Determines whether if there is a path from Sommet source to Sommet sink in the residual graph
         *
         * @return true of there is a path from Sommet source to Sommet sink in the residual graph
         * @param source start of the path
         * @param sink end of the path
         * @param parent parents
        */
        bool BfsExploration(int source, int sink, std::vector<int>& parent);

    private:
        std::vector<std::vector<double>> m_graph; /**graph */
        std::vector<std::vector<double>> m_rgraph; /**residual graph */
};

#endif // GRAPHFLOTS_H
