#include "Arete.h"

Arete::Arete()
{
    //default ctor
}
Arete::Arete(int id, int origin, int target, int weight) : m_id(id), m_origin(origin), m_target(target), m_weight(weight)
{
    //ctor
}

Arete::~Arete()
{
    //dtor
}

std::istream& operator>>(std::istream& stream, Arete& s)
{
    s.m_weight = 1;
    return stream >> s.m_id >> s.m_origin >> s.m_target;
}
