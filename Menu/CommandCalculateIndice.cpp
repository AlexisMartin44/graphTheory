#include "CommandCalculateIndice.h"
#include <iomanip>

CommandCalculateIndice::CommandCalculateIndice()
{
    //ctor
}

CommandCalculateIndice::~CommandCalculateIndice()
{
    //dtor
}

void CommandCalculateIndice::Execute(Graph& g)
{
    char mask = 0b0000;
    if(std::cin.peek() == '\n')
    {
        mask = -1;
    }
    else
    {
        do
        {
            std::string str;
            std::cin >> str;
            if (str == "degree")
                mask |= DEGREE;
            if (str == "proximity")
                mask |= PROXIMITY;
            if (str == "vecteur-propre")
                mask |= VECT_PROPRE;
            if (str == "betweenness")
                mask |= BETWEENNESS;
            if (str == "all")
                mask = -1;
        }
        while(std::cin.peek() != '\n');
    }

    bool save = false;
    {
        std::cout << "Do you want to save the results (y|n) : ";
        std::string s;//string to clear the buffer
        std::cin >> s;
        save = s[0] == 'y';
    }

    if(save)
    {
        remove("indices_degree.txt");
        remove("indices_proximity.txt");
        remove("indices_vecteur_propre.txt");
        remove("indices_betweenness.txt");
    }
    if(mask == -1)// save history and indices
    {
        remove("indices_history.txt");
        remove("indices.txt");
    }

    GraphIndices gi(g);
    IndicesWrapper deg;
    IndicesWrapper prox;
    IndicesWrapper vect;
    IndicesWrapper betw;

    if((mask & DEGREE) != 0)
    {
        deg = gi.CentraliteDegre();
        std::cout << "Id\tDeg\tNorm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << deg[i].first << "\t" << deg[i].second << std::endl;
        }
        std::ofstream f("indices_degree.txt");
        if(f.is_open())
        {
            f << "Id\tDeg\tNorm" << std::endl;
            for(size_t i = 0; i < g.GetOrder(); ++i)
            {
                f << i << "\t" << deg[i].first << "\t" << deg[i].second << std::endl;
            }
            f.close();
        }
        std::cout << "GLOBAL : " << deg.GlobalIndex().first << "\tNorm : " << deg.GlobalIndex().second << std::endl << std::endl;
    }
    if((mask & PROXIMITY) != 0)
    {
        prox = gi.CentraliteProximite();
        std::cout << "Id\tProx\tNorm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << prox[i].first << "\t" << prox[i].second << std::endl;
        }

        std::ofstream f("indices_proximity.txt");
        if(f.is_open())
        {
            f << "Id\tProx\tNorm" << std::endl;
            for(size_t i = 0; i < g.GetOrder(); ++i)
            {
                f << i << "\t" << prox[i].first << "\t" << prox[i].second << std::endl;
            }
            f.close();
        }
        std::cout << "GLOBAL : " << prox.GlobalIndex().first << "\tNorm : " << prox.GlobalIndex().second << std::endl << std::endl;
    }
    if((mask & VECT_PROPRE) != 0)
    {
        vect = gi.CentraliteVecteurPropre();
        std::cout << "Id\tVect" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << vect.GetIndices()[i] << std::endl;
        }
        std::ofstream f("indices_vecteur_propre.txt");
        if(f.is_open())
        {
            f << "Id\tVect" << std::endl;
            for(size_t i = 0; i < g.GetOrder(); ++i)
            {
                f << i << "\t" << vect.GetIndices()[i] << std::endl;
            }
            f.close();
        }
        std::cout << "GLOBAL : " << vect.GlobalIndex().first << std::endl << std::endl;
    }
    if((mask & BETWEENNESS) != 0)
    {
        betw = gi.CentraliteBetweenness();
        std::cout << "Id\tBetw\tNorm" << std::endl;
        for(size_t i = 0; i < g.GetOrder(); ++i)
        {
            std::cout << i << "\t" << betw[i].first << "\t" << betw[i].second << std::endl;
        }
        std::ofstream f("indices_betweenness.txt");
        if(f.is_open())
        {
            f << "Id\tBetw\tNorm" << std::endl;
            for(size_t i = 0; i < g.GetOrder(); ++i)
            {
                f << i << "\t" << betw[i].first << "\t" << betw[i].second << std::endl;
            }
            f.close();
        }
        std::cout << "GLOBAL : " << betw.GlobalIndex().first << "\tNorm : " << betw.GlobalIndex().second << std::endl << std::endl;
    }

    if(mask == -1)
    {
        std::ofstream f("indices_history.txt");
        if(f.is_open())
        {
            f << deg << prox << vect << betw;
            f.close();
        }

        if(save)
        {
            std::ofstream f("indices.txt");
            if(f.is_open())
            {
                f << "Id\tDegree\t\tProximity\tEigen Vector\tBetweenness" << std::endl;
                for(auto s : g.GetSommets())
                {
                    f << s.GetId() << "\t";

                    f << deg[s.GetId()].first << " ";
                    if(deg.NormalizedSize() != 0)
                    {
                        f << deg[s.GetId()].second << "\t";
                    }
                    else
                    {
                        f << "0.00" << "\t";
                    }

                    f << prox[s.GetId()].first << " ";
                    if(prox.NormalizedSize() != 0)
                    {
                        f << prox[s.GetId()].second << "\t";
                    }
                    else
                    {
                        f << "0.00" << "\t";
                    }

                    f << vect.GetIndices()[s.GetId()] << " ";
                    if(vect.NormalizedSize() != 0)
                    {
                        f << vect[s.GetId()].second << "\t";
                    }
                    else
                    {
                        f << "0.00" << "\t";
                    }

                    f << "\t";
                    f << betw[s.GetId()].first << " ";
                    if(betw.NormalizedSize() != 0)
                    {
                        f << betw[s.GetId()].second << "\t";
                    }
                    else
                    {
                        f << "0.00" << "\t";
                    }

                    f << std::endl;
                }
                f.close();
            }
        }
    }
}
