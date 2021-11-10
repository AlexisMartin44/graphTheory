#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>

#include "Constants.h"

constexpr char defcol[] = "black";

/** \brief Contains all the functions called to draw something
*/
class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=SCREEN_WIDTH, int _height=SCREEN_HEIGHT);
        ~Svgfile();

        void AddDisk(double x, double y, double r, std::string color=defcol);
        void AddCircle(double x, double y, double r, double ep, std::string color=defcol);
        void AddTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void AddTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void AddLine(double x1, double y1, double x2, double y2, std::string color, double width);
        void AddCross(double x, double y, double span, std::string color=defcol);

        void AddText(double x, double y, std::string text, std::string color=defcol);
        void AddText(double x, double y, double val, std::string color=defcol);

        void AddGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");
        void AddRectangle(double x1, double y1, double x2, double y2, std::string colorFill, double opacite, std::string colorBordure);

         /**
          * Custom function to draw a Sommet
          *
          * @param x coord_x
          * @param y coord_y
          * @param rayon radius
          * @param couleur color
          * @param name name
          * @param id id
          * @param indice -1 if we do not want to draw the indices
          * @param draw_text false if we do not want to draw the texts
         */
        void AddSommet(double x, double y, double rayon, std::string couleur, std::string name, int id, double indice = -1, bool draw_text = true);
        
         /**
          * Custom function to draw an Arete
          *
          * @param x1 coord_x of Sommet origin
          * @param y1 coord_y of Sommet origin
          * @param x2 coord_x of Sommet target
          * @param y2 coord_y of Sommet target
          * @param rayon radius of Sommet origin
          * @param rayon2 radius of Sommet target
          * @param couleur color
          * @param width width of the Arete
          * @param ponderation whether the graph if weighted or not
          * @param poids weight of the Arete
          * @param oriente wheter the graph if oriented or not
          * @param id id
          * @param draw_text false if we do not want to draw the texts
         */
         void AddArete(double x1, double y1, double x2, double y2, double rayon, double rayon2, std::string couleur, double width, bool ponderation, double poids, bool oriente, int id, bool draw_text = true);

        static std::string MakeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



