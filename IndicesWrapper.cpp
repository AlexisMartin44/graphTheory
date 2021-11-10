#include "IndicesWrapper.h"

#include <algorithm>

void IndicesWrapper::resize(int r, double def, int n)
{
    m_indices.resize(r, def);
    if(n==-1)
        m_indices_normalized.resize(r, def);
    else
        m_indices_normalized.resize(n, def);
}

void IndicesWrapper::SetIndices(double indices, int i)
{
    m_indices[i] = indices;
}

void IndicesWrapper::SetIndicesNormalized(double indices_normalized, int i)
{
    m_indices_normalized[i] = indices_normalized;
}


std::pair<double, double> IndicesWrapper::operator[] (unsigned i)
{
    std::pair<double, double> p(m_indices[i], i >= m_indices_normalized.size() ? 0 : m_indices_normalized[i]);
    return p;
}


std::ostream& operator<<(std::ostream& s, const IndicesWrapper& iw)
{
    s << iw.m_indices.size() << std::endl;
    for(auto& it : iw.m_indices)
    {
        s << it << std::endl;
    }
    s << iw.m_indices_normalized.size() << std::endl;
    for(auto& it : iw.m_indices_normalized)
    {
        s << it << std::endl;
    }
    return s;
}

std::istream& operator>>(std::istream& s, IndicesWrapper& iw)
{
    size_t t;
    s >> t;
    iw.m_indices.resize(t);
    for(size_t i = 0; i < t; ++i)
    {
        s >> iw.m_indices[i];
    }
    s >> t;
    iw.m_indices_normalized.resize(t);
    for(size_t i = 0; i < t; ++i)
    {
        s >> iw.m_indices_normalized[i];
    }
    return s;
}

std::pair<double, double> IndicesWrapper::GlobalIndex()
{
    double index1 = 0, index2 = 0, maximum, indicesSize;
    indicesSize = m_indices.size();

    maximum = *std::max_element(m_indices.begin(), m_indices.end());
    for(size_t i = 0 ; i < indicesSize ; ++i)
    {
        index1 += maximum - m_indices[i];
    }
    index1 /= ((pow(indicesSize, 2) - (3 * indicesSize) + 2)) / ((2 * indicesSize) - 3);

    if(m_indices_normalized.size()>0)
    {
        maximum = *std::max_element(m_indices_normalized.begin(), m_indices_normalized.end());
        for(size_t i = 0 ; i < indicesSize ; ++i)
        {
            index2 += maximum - m_indices_normalized[i];
        }
        index2 /= ((pow(indicesSize, 2) - (3 * indicesSize) + 2)) / ((2 * indicesSize) - 3);
    }

    std::pair<double, double> p(index1, index2);

    return p;
}
