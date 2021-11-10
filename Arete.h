#ifndef ARRETE_H
#define ARRETE_H

#include <istream>

/**
 * \brief Contains all informations about the relation between two Sommet
 */
class Arete
{
    public:
        /**
         * Default constructor
         */
        Arete();
        
        /**
         * All values constructor
         */
        Arete(int id, int origin, int target, int weight = 1);
        
        /**
         * Default destructor
         */
        virtual ~Arete();

        /**
         * Takes the important values from the stream to create an Arete
         */
        friend std::istream& operator>>(std::istream &input, Arete& s);

        /**
         * Accesses the id of an Arete
         *
         * @return the id of the Arete
         */
        inline int GetId() const { return m_id; }
        
        /**
         * Sets the id of an arete
         *
         * @param val value to set
         */
        inline void SetId(int val) { m_id = val; }
        
        /**
         * Accesses the id of the Sommet origin
         *
         * @return the id of the Sommet origin
         */
        inline int GetOrigin() const { return m_origin; }
    
        /**
         * Sets the id of the Sommet origin
         *
         * @param val the value to set
         */
        inline void SetOrigin(int val) { m_origin = val; }
        
        /**
         * Accesses the id of the Sommet target
         *
         * @return the id of the Sommet target
         */
        inline int GetTarget() const { return m_target; }
    
        /**
         * Sets the id of the Sommet target
         *
         * @param val the value to set
         */
        inline void SetTarget(int val) { m_target = val; }
        
        /**
         * Accessess the weight of an Arete
         *
         * @return the weight of the Arete
         */
        inline double GetWeight() const { return m_weight; }
    
        /**
         * Sets the weight of an Arete
         *
         * @param val the value to set
         */
        inline void SetWeight(double val) { m_weight = val; }

    private:
        int m_id; /** id of the Arete*/
        int m_origin; /** id of the Sommet origin */
        int m_target; /** id of the Sommet target */
        double m_weight; /** weight of the Arete */
};

#endif // ARRETE_H
