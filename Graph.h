#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <set>
#include <stack>
#include <iostream>

#include "Arete.h"
#include "Sommet.h"
#include "GraphFlow.h"
#include "Constants.h"
#include "utility.h"

/**
 * \brief Contains all informations about the Graph : Sommet, Arete
 */
class Graph
{
    public:
        /**
         * Default constructor
         */
        Graph();
    
        /**
         * Default destructor
         */
        virtual ~Graph();

        /**
         * Loads the topology from the file into the Graph
         *
         * \param path the path of the file containing the topology
         */
        void LoadTopology(std::string path);

        /**
         * Loads the weights from the file into the Graph
         *
         * \param path the path of the file containing the weights
         */
        void LoadWeights(std::string path);

        /**
         * Loads the topology and the weights of the Graph
         *
         * \param topology path of the topology file
         * \param weights path of the weights file, optional
         */
        void Load(std::string topology, std::string weights = "");

        /**
         * Prints the informations about the Graph
         */
        friend std::ostream& operator<<(std::ostream& stream, Graph& graph);
    
        /** Accesses m_sommets
         * \return the current value of m_sommets
         */
    
        inline std::vector<Sommet>& GetSommets() { return m_sommets; }
        
        /**
         * Accesses m_sommets
         * \return the current value of m_sommets
         */
        inline const std::vector<Sommet>& GetConstSommets() const { return m_sommets; }
        
        /** Accesses m_aretes
         * \return the current value of m_aretes
         */
    
        inline std::vector<Arete>& GetAretes() { return m_aretes; }
        
        /**
         * Accesses m_aretes
         * \return the current value of m_aretes
         */
        inline const std::vector<Arete>& GetConstAretes() const { return m_aretes; }
        
        /**
         * Acceses m_deleted
         * \return the current value of m_deleted
        */
        inline std::set<int>& GetDeleted() { return m_deleted; }
        
        /**
         * Acceses m_deleted
         * \return the current value of m_deleted
        */
        inline const std::set<int>& GetConstDeleted() const { return m_deleted; }
        
        /**
         * Accesses m_weighted
         * \return the current value of m_weighted
         */
        inline bool GetWeighted() const { return m_weighted; }
        
        /**
         * Accesses m_topologyPath
         * \return the current value of m_topologyPath
         */
        inline std::string GetTopologyPath() const { return m_topologyPath; }
        
        /**
         * Accesses m_weightPath
         * \return the current value of m_weightPath
         */
        inline std::string GetWeightPath() const { return m_weightPath; }
        
        /**
         * Gets the value of the boolean m_oriente
         *
         * @return whether the Graph is oriented or not
         */
        inline bool GetOriente() const { return m_oriente; }

        /**
         * Gets the order of the Graph
         * \return the order of the Graph
         */
        inline unsigned long GetOrder() const { return m_sommets.size(); }
        
        /**
         * Gets the the number of edges of the Graph
         * \return the number of edges of the Graph
         */
        inline unsigned long GetSizeAretes() const { return m_aretes.size() - m_deleted.size(); }
        
        /**
         * Accesses the siblings from the Sommet of indice id
         * \return The siblings from id
         * @param id id of the Sommet in question
         */
        std::vector<std::pair<double, const Sommet&>> GetSiblings(int id) const;
        
        /**
         * Accesses the siblings from the Sommet of indice id, the edges connecting towards the Sommet being weighted negatively
         * \return the number siblings from id
         * @param id id of the Sommet in question
         */
        int CountSiblings(int id) const;

        /**
         * Calculates the K-edge-connectivity using the flow method (see GraphFlow)
         * @return the value of k in k-connectivity
        */
        int KConnectivity();// not const since we need to temporarily modify the orientation

        /**
         * Calculates the K-strong-edge-connectivity using the flow method (see GraphFlow)
         * This correspond to the amount of edges to remove to stop the Graph from being strongly connected
         * @return 0 if the Graph isn't strongly connected
        */
        int KStrongConnectivity() const;

        /**
         * Says wheter the Graph is connexe or not
         * @return a boolean linked to the connectedness of the Graph
         */
        bool IsConnexe() const;
        
        /**
         * Uses the Tarjan algorithm to count the strongly connected components
         * \return the number of strongly connected components
         */
        int CountStronglyConnectedComponent() const;

        /**
         * Says whether the Graph is strongly connexe or not
         * @return a boolean linked to the strong-connectedness of the Graph
         */
        inline bool IsStronglyConnexe() const{ return CountStronglyConnectedComponent() == 1; }

        void Dijkstra(int depart, int arrivee);
        void AddGreenEdges(std::vector<int> predecesseur, int num, std::set<int>& aretesVertes);

    private:
        std::vector<Sommet> m_sommets; /** vector containing all the Sommet */
        std::vector<Arete> m_aretes; /** vector containing all the Arete */
        bool m_oriente; /** boolean to know if the Graph is oriented */
        bool m_weighted; /** bolean to know if the Graph is weighted */
        std::set<int> m_deleted; /** set of ids of deleted Sommet */

        std::string m_topologyPath = ""; /** name of the topology file path */
        std::string m_weightPath = ""; /** name of the weight file path */

        void TarjanStrongConnect(int id, int& discoverId, int& sccCount, std::stack<int>& st, std::vector<int>& indexes, std::vector<int>& lowlinks, std::vector<bool>& onStack) const;
};

#endif // GRAPH_H
