#include "CommandComparaison.h"

CommandComparaison::CommandComparaison()
{
    //ctor
}

CommandComparaison::~CommandComparaison()
{
    //dtor
}

void CommandComparaison::Execute(Graph& g)
{
    IndicesWrapper deg, prox, vect, betw;
    std::ifstream ifs("indices_history.txt");
    if(ifs.is_open())
    {
        ifs >> deg >> prox >> vect >> betw;
        ifs.close();
        if((int)g.GetOrder() != deg.Size())
        {
            std::cout << "The current history file does not match the loaded graph, please recalculate the indices of the original graph with the 'indices' command" << std::endl;
            return;
        }
        GraphIndices gi(g);
        IndicesWrapper deg2 = gi.CentraliteDegre();
        IndicesWrapper prox2 = gi.CentraliteProximite();
        IndicesWrapper vect2 = gi.CentraliteVecteurPropre();
        IndicesWrapper betw2 = gi.CentraliteBetweenness();
        std::cout << "The following displays the originals indices, then the newly calculated ones, and then the variation between the two" << std::endl;

        std::cout << std::endl << "Id\tDeg1\tNorm1\t\tDeg2\tNorm2\t\tVar\tNorm\t\tGlobal1\tNorm1\t\tGlobal2\tNorm2    Var    Norm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << deg[i].first << "\t" << deg[i].second << "\t\t";
            std::cout << deg2[i].first << "\t" << deg2[i].second << "\t\t";
            std::cout << deg2[i].first - deg[i].first << "\t" << deg2[i].second - deg[i].second;
            if(i == g.GetOrder()/2)
            {
                std::cout << "\t\t" << deg.GlobalIndex().first << "\t" << deg.GlobalIndex().second << "\t\t" << deg2.GlobalIndex().first << "\t";
                std::cout << deg.GlobalIndex().second << "\t" << deg2.GlobalIndex().first - deg.GlobalIndex().first << "    ";
                std::cout << deg2.GlobalIndex().second - deg.GlobalIndex().second << std::endl;
            }
            else
                std::cout << std::endl;
        }

        std::cout << std::endl;

        std::cout << "Id\tProx1\tNorm1\t\tProx2\tNorm2\t\tVar\tNorm\t\tGlobal1\tNorm1\t\tGlobal2\tNorm2    Var    Norm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << prox[i].first << "\t" << prox[i].second << "\t\t";
            std::cout << prox2[i].first << "\t" << prox2[i].second << "\t\t";
            std::cout << prox2[i].first - prox[i].first << "\t" << prox2[i].second - prox[i].second;
            if(i == g.GetOrder()/2)
            {
                std::cout << "\t\t" << prox.GlobalIndex().first << "\t" << prox.GlobalIndex().second << "\t\t" << prox2.GlobalIndex().first << "\t";
                std::cout << prox2.GlobalIndex().second << "\t" << prox2.GlobalIndex().first - prox.GlobalIndex().first << "    ";
                std::cout << prox2.GlobalIndex().second - prox.GlobalIndex().second << std::endl;
            }
            else
                std::cout << std::endl;
        }

        std::cout << std::endl;

        std::cout << "Id\tVect1\t\tVect2\t\tVar\t\tGlobal1\t\tGlobal2\t\tVar" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << vect.GetIndices()[i] << "\t\t";
            std::cout << vect2.GetIndices()[i] << "\t\t";
            std::cout << vect2.GetIndices()[i] - vect.GetIndices()[i];
            if(i == g.GetOrder()/2)
            {
                std::cout << "\t\t" << vect.GlobalIndex().first << "\t\t" << vect2.GlobalIndex().first << "\t\t";
                std::cout << vect2.GlobalIndex().first - vect.GlobalIndex().first << std::endl;
            }
            else
                std::cout << std::endl;
        }

        std::cout << std::endl;

        std::cout << "Id\tBetw1\tNorm1\t\tBetw2\tNorm2\t\tVar\tNorm\t\tGlobal1\tNorm1\t\tGlobal2\tNorm2    Var    Norm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << betw[i].first << "\t" << betw[i].second << "\t\t";
            std::cout << betw2[i].first << "\t" << betw2[i].second << "\t\t";
            std::cout << betw2[i].first - betw[i].first<< "\t" << betw2[i].second - betw[i].second;
            if(i == g.GetOrder()/2)
            {
                std::cout << "\t\t" << betw.GlobalIndex().first << "\t" << betw.GlobalIndex().second << "\t\t" << betw2.GlobalIndex().first << "\t";
                std::cout << betw2.GlobalIndex().second << "\t" << betw2.GlobalIndex().first - betw.GlobalIndex().first << "    ";
                std::cout << betw2.GlobalIndex().second - betw.GlobalIndex().second << std::endl;
            }
            else
                std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    else
    {
        std::cout << "Couldn't find any history file, please calculate the indices of the original graph with the 'indices' command" << std::endl;
    }
}
