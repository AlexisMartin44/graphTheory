#include "GraphIndices.h"


GraphIndices::GraphIndices(const Graph& graph) : m_graph(graph)
{
    //ctor
}

GraphIndices::~GraphIndices()
{
    //dtor
}

IndicesWrapper GraphIndices::CentraliteDegre()
{
    IndicesWrapper iw;
    double deg = (double)m_graph.GetOrder();
    iw.resize(deg);
    for(auto s : m_graph.GetConstSommets())
    {
        iw.SetIndices(m_graph.CountSiblings(s.GetId()), s.GetId());
        iw.SetIndicesNormalized(m_graph.CountSiblings(s.GetId()) / (double)(m_graph.GetOrder() - 1), s.GetId());
    }
    return iw;
}

IndicesWrapper GraphIndices::CentraliteVecteurPropre()
{
    IndicesWrapper iw;
    iw.resize(m_graph.GetOrder(), 1, 0);
    std::vector<double> c(m_graph.GetOrder(), 0);
    double lambda = 0, prev_lambda = 0, sum = 0;
    do
    {
        for(auto s : m_graph.GetConstSommets())
        {
            sum = 0;
            for(auto sib : m_graph.GetSiblings(s.GetId()))
            {
                sum += iw.GetIndices()[sib.second.GetId()];
            }
            c[s.GetId()] = sum;
        }
        prev_lambda = lambda;
        sum = 0;
        for(auto temp : c)
        {
            sum += pow(temp, 2);
        }
        lambda = sqrt(sum);
        for(auto s : m_graph.GetConstSommets())
        {
            iw.SetIndices(lambda == 0 ? 0 : c[s.GetId()] / lambda, s.GetId());
        }
    } while(std::abs(lambda - prev_lambda) >= DELTA_LAMBDA);
    return iw;
}

auto cmp = [] (std::pair<int, double> p1, std::pair<int, double> p2)
{
    return p2.second< p1.second;
};

void GraphIndices::IndexCalculation(std::vector<int> predecesseur, int num, int& shortestPath)
{
    if(predecesseur[num]!=-1)
    {
        if(m_graph.GetWeighted())
        {
            for(auto &a : m_graph.GetConstAretes())
            {
                if(a.GetTarget() == predecesseur[num] && a.GetOrigin() == num)
                    shortestPath += a.GetWeight();
            }
        }
        else
        {
            for(auto &a : m_graph.GetConstAretes())
            {
                if((a.GetTarget() == predecesseur[num] && a.GetOrigin() == num) || (a.GetTarget() == num && a.GetOrigin() == predecesseur[num]))
                    shortestPath += a.GetWeight();
            }
        }
        IndexCalculation(predecesseur, predecesseur[num], shortestPath);
    }
}

void GraphIndices::Dijkstra(unsigned firstPoint, IndicesWrapper& iw)
{
    std::vector<int> predecesseur;
    std::vector<bool> marquage;
    std::pair<int, double> closer;
    std::vector<double> distance;
    int shortestPath = 0;

    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(cmp) > file(cmp);

    for(unsigned i=0; i < m_graph.GetOrder(); ++i)
    {
        predecesseur.push_back(-1);
        marquage.push_back(false);
        if(i!=firstPoint)
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
        for(auto &i : m_graph.GetSiblings(closer.first))
        {
            if(distance[i.second.GetId()] > closer.second + i.first && marquage[i.second.GetId()] == false)
            {
                distance[i.second.GetId()] = closer.second + i.first;
                file.push({i.second.GetId(), distance[i.second.GetId()]});
                predecesseur[i.second.GetId()] = closer.first;
            }
        }
    }while(!file.empty());

    for(size_t i=0; i<m_graph.GetOrder(); ++i)
    {
        IndexCalculation(predecesseur, i, shortestPath);
    }

    if(shortestPath!=0)
    {
        iw.SetIndices(1.0/shortestPath, firstPoint);
        iw.SetIndicesNormalized((m_graph.GetOrder() - 1.0) / shortestPath, firstPoint);
    }
    else
    {
       iw.SetIndices(0.0, firstPoint);
       iw.SetIndicesNormalized(0.0, firstPoint);
    }
}

IndicesWrapper GraphIndices::CentraliteProximite()
{
    IndicesWrapper iw;
    iw.resize(m_graph.GetOrder());
    for(size_t i = 0; i < m_graph.GetOrder(); ++i)
    {
        Dijkstra((unsigned int)i, iw);
    }
    return iw;
}

IndicesWrapper GraphIndices::CentraliteBetweenness()
{
    IndicesWrapper iw;
    iw.resize(m_graph.GetOrder());
    for(auto& it : m_graph.GetConstSommets())
    {
        std::stack<int> st;
        std::vector<std::list<int>> p(m_graph.GetOrder());
        std::vector<int> sigma(m_graph.GetOrder(), 0);
        sigma[it.GetId()] = 1;
        std::vector<int> d(m_graph.GetOrder(), -1);
        d[it.GetId()] = 0;
        std::queue<int> qu;
        qu.push(it.GetId());
        while(!qu.empty())
        {
            int id = qu.front();
            qu.pop();
            st.push(id);
            for(auto& sibling : m_graph.GetSiblings(id))
            {
                if(d[sibling.second.GetId()] < 0)
                {
                    qu.push(sibling.second.GetId());
                    d[sibling.second.GetId()] = d[id] + sibling.first;// modif here : use weight instead of 1
                }

                if(d[sibling.second.GetId()] == d[id] + sibling.first)// modif here too
                {
                    sigma[sibling.second.GetId()] += sigma[id];
                    p[sibling.second.GetId()].push_back(id);
                }
            }
        }

        std::vector<double> delta(m_graph.GetOrder(), 0);
        while(!st.empty())
        {
            int id = st.top();
            st.pop();
            for(auto& pred : p[id])
            {
                delta[pred] += (sigma[pred] / (double)sigma[id]) * (1 + delta[id]);
            }
            if(id != it.GetId())
            {
                iw.SetIndices(iw[id].first+delta[id], id);
            }
        }
    }

    for(size_t i = 0; i < m_graph.GetOrder(); ++i)
    {
        iw.SetIndicesNormalized(2 * iw[i].first / (m_graph.GetOrder()*m_graph.GetOrder() - 3 * m_graph.GetOrder() + 2), i);
    }

    return iw;
}

IndicesWrapper GraphIndices::AverageCentralites(std::vector<IndicesWrapper> viw)
{
    IndicesWrapper iw;
    if(viw.size() == 0)
    {
        std::cout << "Empty vector!" << std::endl;
        return iw;
    }
    bool nonnul = false;
    for(auto in : viw)
    {
        if(in.NormalizedSize() == 0) // then at least one indice isnt normalized
        {
            nonnul = true;
            break;
        }
    }
    iw.resize(viw[0].Size(), nonnul ? 0 : viw[0].NormalizedSize());
    for(auto in : viw)
    {
        for(int i = 0; i < iw.Size(); ++i)
        {
            iw.SetIndices(iw.GetIndices()[i] + in.GetIndices()[i], i); // sum all indices for each node
            if(!nonnul)
            {
                iw.SetIndicesNormalized(iw[i].second + in[i].second, i); // sum all normalized indices for each node
            }
        }
    }
    for(int i = 0; i < iw.Size(); ++i)
    {
        iw.SetIndices(iw[i].first / viw.size(), i); // average of all indices for each node
        if(!nonnul)
        {
            iw.SetIndicesNormalized(iw[i].second / viw.size(), i); // average of all normalized indices for each node
        }
    }
    return iw;
}
