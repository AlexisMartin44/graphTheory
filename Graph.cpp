#include "Graph.h"
#include "utility.h"
#include "GraphDrawer.h"

#include <sstream>

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::LoadTopology(std::string path)
{
    std::ifstream f(path);
    if(!f.is_open())
    {
        ExitApplication("Couldn't read topology file!");
    }
    try
    {
        int temp;
        f >> temp;
        m_oriente = (temp == 1);
        f >> temp;
        m_sommets.resize(temp);// ignore previous values, they are gonna get overwritten anyway
        for(auto& it : m_sommets)
        {
            f >> it;
        }
        f >> temp;
        m_aretes.resize(temp);// same here
        for(auto& it : m_aretes)
        {
            f >> it;
        }
        m_weighted = false;
        m_deleted.clear();

        m_topologyPath = path;
        m_weightPath = "";
    }
    catch(...)
    {
        ExitApplication("An error occured while reading the topology file!");
    }
}

void Graph::LoadWeights(std::string path)
{
    std::ifstream f(path);
    if(!f.is_open())
    {
        ExitApplication("Couldn't read weights file!");
    }
    try
    {
        int temp;
        f >> temp;
        if(temp != (int)m_aretes.size())
        {
            std::cout << "There isn't as much connections in the weight file as in the loaded graph";
        }
        else
        {
            float w;
            for(auto& it : m_aretes)
            {
                f >> w >> w;
                it.SetWeight(w);
            }
            m_weighted = true;
            m_weightPath = path;
        }
    }
    catch(...)
    {
        ExitApplication("An error occured while reading the weights file!");
    }
}

void Graph::Load(std::string topology, std::string weights)
{
    LoadTopology(topology);
    if(weights != "")
    {
        LoadWeights(weights);
    }
}

std::vector<std::pair<double, const Sommet&>> Graph::GetSiblings(int id) const
{
    std::vector<std::pair<double, const Sommet&>> ret;
    for(auto& it : m_aretes)
    {
        if(m_deleted.count(it.GetId())==0)
        {
            if(it.GetOrigin() == id)
            {
                ret.push_back({it.GetWeight(), m_sommets[it.GetTarget()]});
            }
            else if(!m_oriente && it.GetTarget() == id)
            {
                ret.push_back({it.GetWeight(), m_sommets[it.GetOrigin()]});
            }
        }
    }
    return ret;
}

int Graph::CountSiblings(int id) const
{
    int ret = 0;
    for(auto& it : m_aretes)
    {
        if(m_deleted.count(it.GetId())==0)
        {
            if(it.GetOrigin() == id || (!m_oriente && it.GetTarget() == id))
            {
                ret++;
            }
        }
    }
    return ret;
}

int Graph::KConnectivity()
{
    bool b = m_oriente;// simple connectivity doesn't take into account the orientation
    m_oriente = 0;
    GraphFlow gf(*this);
    int k = INFINI;
    for(size_t i = 1; i < GetOrder(); i++)
    {
        k = MIN(k, gf.Flow(0, i));
    }
    m_oriente = b;
    return k;
}

int Graph::KStrongConnectivity() const
{
    // K Strong Connectivity only makes sense for strongly connected graphs
    if(!IsStronglyConnexe())
        return 0;
    GraphFlow gf(*this);
    int k = 500000;
    for(size_t i = 1; i < GetOrder(); i++)
    {
        k = MIN(k, gf.Flow(0, i));
    }
    return k;
}

bool Graph::IsConnexe() const
{
    std::stack<int> st;
    std::set<int> discovered;
    st.push(0);
    while(!st.empty())
    {
        const Sommet& s = m_sommets[st.top()];
        st.pop();
        for(auto& it : m_aretes)
        {
            if(m_deleted.count(it.GetId())==0)
            {
                if(it.GetOrigin() == s.GetId())
                {
                    if(discovered.find(it.GetTarget()) == discovered.end())
                    {
                        st.push(it.GetTarget());
                    }
                }
                else if(!m_oriente && it.GetTarget() == s.GetId())
                {
                    if(discovered.find(it.GetOrigin()) == discovered.end())
                    {
                        st.push(it.GetOrigin());
                    }
                }
            }
        }
        discovered.insert(s.GetId());
    }
    return discovered.size() == GetOrder();
}

int Graph::CountStronglyConnectedComponent() const
{
    std::stack<int> st;
    std::vector<int> indexes(GetOrder(), -1);
    std::vector<int> lowlinks(GetOrder(), -1);
    std::vector<bool> onStack(GetOrder(), false);
    int discoverId = 0;
    int sccCount = 0;
    for(auto& it : m_sommets)
    {
        if(indexes[it.GetId()] == -1)
        {
            TarjanStrongConnect(it.GetId(), discoverId, sccCount, st, indexes, lowlinks, onStack);
        }
    }
    return sccCount;
}

void Graph::TarjanStrongConnect(int id, int& discoverId, int& sccCount, std::stack<int>& st, std::vector<int>& indexes, std::vector<int>& lowlinks, std::vector<bool>& onStack) const
{
    indexes[id] = discoverId;
    lowlinks[id] = discoverId;
    discoverId++;
    st.push(id);
    onStack[id] = true;

    for(auto& it : GetSiblings(id))
    {
        if(indexes[it.second.GetId()] == -1)
        {
            TarjanStrongConnect(it.second.GetId(), discoverId, sccCount, st, indexes, lowlinks, onStack);
            lowlinks[id] = MIN(lowlinks[id], lowlinks[it.second.GetId()]);
        }
        else if(onStack[it.second.GetId()])
        {
            lowlinks[id] = MIN(lowlinks[id], indexes[it.second.GetId()]);
        }
    }

    if(lowlinks[id] == indexes[id])// new SCC
    {
        sccCount++;
        while(!st.empty())
        {
            // TODO add sommet to SCC
            onStack[st.top()] = false;
            st.pop();
        }
        // TODO add scc to output
    }
}

std::ostream& operator<<(std::ostream& stream, Graph& graph)
{
    stream << (graph.m_oriente ? "Oriented" : "Non oriented") << (graph.m_weighted ? " weighted" : "") << (graph.IsStronglyConnexe() ? " and strongly connexe" : "");
    stream << " graph of order " << graph.GetOrder() << " with " << graph.m_aretes.size() << " connections" << std::endl;
    stream << "The graph is " << graph.KConnectivity() << "-edges-connected";
    if(graph.m_oriente)
    {
        stream << " and " << graph.KStrongConnectivity() << "-strongly-edges-connected";
    }
    return stream << std::endl;
}

auto cmp = [] (std::pair<int, double> p1, std::pair<int, double> p2)
{
    return p2.second< p1.second;
};

void Graph::AddGreenEdges(std::vector<int> predecesseur, int num, std::set<int>& aretesVertes)
{
    if(predecesseur[num] != -1)
    {
        if(GetOriente())
        {
            for(auto &a : GetConstAretes())
            {
                if(a.GetTarget() == num && a.GetOrigin() == predecesseur[num])
                    aretesVertes.insert(a.GetId());
            }
        }
        else
        {
            for(auto &a : GetConstAretes())
            {
                if((a.GetTarget() == predecesseur[num] && a.GetOrigin() == num) || (a.GetTarget() == num && a.GetOrigin() == predecesseur[num]))
                    aretesVertes.insert(a.GetId());
            }
        }

        AddGreenEdges(predecesseur, predecesseur[num], aretesVertes);
    }
}

void Graph::Dijkstra(int depart, int arrivee)
{
    std::vector<int> predecesseur;
    std::vector<bool> marquage;
    std::pair<int, double> closer;
    std::vector<double> distance;
    std::set<int> aretesVertes;

    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(cmp) > file(cmp);

    for(unsigned i=0; i < GetOrder(); ++i)
    {
        predecesseur.push_back(-1);
        marquage.push_back(false);
        if( i!= (unsigned)depart)
        {
            distance.push_back(INFINI);
        }
        else
            distance.push_back(0);

        file.push({i, distance[i]});
    }
    do
    {
        do
        {
            closer = file.top();
            file.pop();
        }while(marquage[closer.first] == true && !file.empty());

        marquage[closer.first] = true;
        for(auto &i : GetSiblings(closer.first))
        {
            if(distance[i.second.GetId()] > closer.second + i.first && marquage[i.second.GetId()] == false)
            {
                distance[i.second.GetId()] = closer.second + i.first;
                file.push({i.second.GetId(), distance[i.second.GetId()]});
                predecesseur[i.second.GetId()] = closer.first;
            }
        }
    }while(!file.empty());

    AddGreenEdges(predecesseur, arrivee, aretesVertes);

    std::cout << "Enter a size [width, height] or enter to skip : ";
    int width = SCREEN_WIDTH, height = SCREEN_HEIGHT;
    std::string name;

    std::getline(std::cin, name); //ignore the \n
    std::getline(std::cin, name);
    if(name != "")
    {
        std::stringstream iss(name);
        iss >> width;
        iss >> height;
    }
    GraphDrawer gd("output.svg", width, height);
    gd.DrawShortestPath(*this, aretesVertes);
}
