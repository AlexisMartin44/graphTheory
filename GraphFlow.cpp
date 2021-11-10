#include "GraphFlow.h"

// avois circular dependencies
#include "Graph.h"

GraphFlow::GraphFlow(const Graph& g, bool useWeights)
{
    // build adj matrix
    m_graph.resize(g.GetOrder(), std::vector<double>(g.GetOrder(), 0));
    for(auto& it : g.GetConstSommets())
    {
        for(auto& sib : g.GetSiblings(it.GetId()))
        {
            m_graph[it.GetId()][sib.second.GetId()] += useWeights ? sib.first : 1;
        }
    }
}

GraphFlow::~GraphFlow()
{
    //dtor
}

bool GraphFlow::BfsExploration(int source, int sink, std::vector<int>& parent)
{
    std::vector<bool> visited(m_rgraph.size(), false);
    std::queue<int> qu;
    qu.push(source);
    visited[source] = true;

    while(!qu.empty())
    {
        int id = qu.front();
        qu.pop();

        for (size_t v=0; v<m_rgraph.size(); v++)
        {
            if (visited[v]==false && m_rgraph[id][v] > 0)
            {
                qu.push(v);
                parent[v] = id;
                visited[v] = true;
            }
        }
    }
    return visited[sink];// could this be moveed in the for to get faster?
}

double GraphFlow::Flow(int source, int sink)
{
    m_rgraph = m_graph;// copy into residual graph

    std::vector<int> parent(m_rgraph.size());
    double max_flow = 0;

    while(BfsExploration(source, sink, parent))// we can augment the flow
    {
        double path_flow = 999999;// should be high enough

        for(int id = sink; id != source; id = parent[id])
        {
            path_flow = MIN(path_flow, m_rgraph[parent[id]][id]);
        }

        max_flow += path_flow;

        for(int id = sink; id != source; id = parent[id])
        {
            int u = parent[id];
            m_rgraph[u][id] -= path_flow;
            m_rgraph[id][u] += path_flow;
        }
    }

    return max_flow;
}
