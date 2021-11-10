
//
//  IndicesWrapper.h
//  PiscineING2
//
//  Created by Titouan Lermite on 27/04/2020.
//  Copyright © 2020 Titouan Lermite. All rights reserved.
//

#ifndef IndicesWrapper_h
#define IndicesWrapper_h

#include <vector>
#include <iostream>
#include <cmath>

/**
 * \brief Contains all the informationsn about the indices
*/
class IndicesWrapper
{
private:
    std::vector<double> m_indices; /** normal indices*/
    std::vector<double> m_indices_normalized; /** normalized indices*/
public:
    /**
     * Accesses m_indices.size()
     *
     * \return the current size of m_indices
     */
    inline int Size(){return m_indices.size();}
    
    /**
     * Accesses m_indices_normalized.size()
     *
     * \return the current size of m_indices_normalized
     */
    inline int NormalizedSize() {return m_indices_normalized.size();}
    
    /**
     * Accesses m_indices
     *
     * \return the current value of m_indices
     */
    inline std::vector<double> &GetIndices() {return m_indices; }

    /**
     * Sets m_indices[i]
     *
     * \param indices value that we want to assign to m_indices[i]
     * @param i Sommet i
     */
    void SetIndices(double indices, int i);
    
    /**
     * Sets m_indices_normalized[i]
     *
     * \param indices_normalized value that we want to assign to m_indices_normalized[i]
     * @param i Sommet i
     */
    void SetIndicesNormalized(double indices_normalized, int i);

    /**
     * Sets the size of m_indices_normalized and m_indices
     *
     * \param r the size that we want to assign to m_indices and m_indices_normalized if n != -1 else
     * \param def the default value
     * @param n the size that we want to assign to m_inndices_normalized
     */
    void resize(int r, double def = 0, int n = -1);

    /**
     * Accesses to the value of m_indices[i] and m_indices_normalized[i]
     *
     * @return a pair of the indices and normalized_indices of the Sommet i
     * \param i the id of the Sommet concerned
     */
    std::pair<double, double> operator[] (unsigned i);

    /**
     * Accessess to the value of m_indices and m_indicess_normalized
     *
     * @return a pair of the global indices and normalized_indices
     */
    std::pair<double,double> GlobalIndex();

    /**
     * Prints the informations about the indices
     */
    friend std::ostream& operator<<(std::ostream& stream, const IndicesWrapper& iw);
    
    /**
     * Takes the important values from the stream to create an IndicesWrapper
     */
    friend std::istream& operator>>(std::istream& stream, IndicesWrapper& iw);
};

#endif /* IndicesWrapper_h */
