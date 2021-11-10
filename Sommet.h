#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <istream>

/**
 * \brief Basic building block of all Graph
 */
class Sommet
{
    public:
        /**
         * Default constructor
         */
        Sommet();
        
        /**
         * All values constructor
         */
        Sommet(int id, std::string name, int x, int y);
        
        /**
         * Default destructor
         */
        virtual ~Sommet();

        /**
         * Takes the important values from the stream to create a Sommet
         */
        friend std::istream& operator>>(std::istream &input, Sommet& s);

        /**
         * Accesses the id of a Sommet
         *
         * @return the id of the Sommet
         */
        inline int GetId() const { return m_id; }
    
        /**
         * Sets the id of a Sommet
         *
         * @param val the value to set
         */
        inline void SetId(int val) { m_id = val; }
    
        /**
         * Accesses the name of a Sommet
         *
         * @return the name of the Sommet
         */
        inline std::string GetName() const { return m_name; }
    
        /**
         * Sets the name of a Sommet
         *
         * @param val the value to set
         */
        inline void SetName(std::string val) { m_name = val; }
    
        /**
         * Accesses the coord_x of a Sommet
         *
         * @return the coord_x of the Sommet
         */
        inline int GetX() const { return m_x; }
    
        /**
         * Sets the coord_x of a sommet
         *
         * @param val the value to set
         */
        inline void SetX(int val) { m_x = val; }
    
        /**
         * Accesses the coord_y of a Sommet
         *
         * @return the coord_y of the sommet
         */
        inline int GetY() const { return m_y; }
    
        /**
         * Sets the coord_y of a Sommet
         *
         * @param val the value to set
         */
        inline void SetY(int val) { m_y = val; }

    private:
        int m_id; /** id of the Sommet */
        std::string m_name; /** name of the Sommet */
        int m_x; /** coord_x of the Sommet */
        int m_y; /** coord_y of the Sommet */
};

#endif // SOMMET_H
