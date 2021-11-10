#include "Sommet.h"

Sommet::Sommet()
{
    // default ctor
}
Sommet::Sommet(int id, std::string name, int x, int y) : m_id(id), m_name(name), m_x(x), m_y(y)
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}

std::istream& operator>>(std::istream& stream, Sommet& s)
{
    return stream >> s.m_id >> s.m_name >> s.m_x >> s.m_y;
}

