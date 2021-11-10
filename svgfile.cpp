#include "svgfile.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <string>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{


    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    //std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::AddDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::AddCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << "/>\n";
}

void Svgfile::AddTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::AddTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::AddLine(double x1, double y1, double x2, double y2, std::string color, double width)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << attrib("stroke-width", width)
            << "/>\n";
}

void Svgfile::AddCross(double x, double y, double span, std::string color)
{
    AddLine(x-span, y-span, x+span, y+span, color, 1);
    AddLine(x-span, y+span, x+span, y-span, color, 1);
}

void Svgfile::AddText(double x, double y, std::string text, std::string color)
{
    m_ostrm << "<text "
            << attrib("text-anchor", "middle")
            << attrib("alignment-baseline", "middle")
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::AddText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    AddText(x, y, oss.str(), color);
}

void Svgfile::AddGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        AddLine(0, y, m_width, y, color, 1);
        if (numbering)
            AddText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        AddLine(x, 0, x, m_height, color, 1);
        if (numbering)
            AddText(x+5, 15, x, color);
        x+=span;
    }
}

void Svgfile::AddRectangle(double x1, double y1, double x2, double y2, std::string colorFill, double opacite, std::string colorBordure)
{
    if(colorBordure == "")
        colorBordure = "transparent";

    m_ostrm << "<rect "
            << attrib("x", x1)
            << attrib("y", y1)
            << attrib("width", x2)
            << attrib("height", y2)
            << attrib("stroke", colorBordure)
            << attrib("fill", colorFill)
            << attrib("opacity", opacite)
            << "/>\n";
}

void Svgfile::AddSommet(double x, double y, double rayon, std::string couleur, std::string name, int id, double indice, bool draw_text)
{
    AddDisk(x, y, rayon, couleur);
    if(draw_text)
    {
        AddText(x - (0.5 * rayon), y, id, "white");
        AddText(x + (0.5 * rayon), y, name, "rgb(153, 0, 76)");
        if(indice != -1)
        {
            couleur = couleur.substr(4);
            std::string col = "rgb(", temp = "";
            for(auto c : couleur)
            {
                if((c == ' ') || (c == ')'))
                {
                    col += std::to_string(255 - std::stoi(temp));
                    if(c != ')')
                        col += ", ";
                    else
                        col += ")";
                    temp = "";
                }
                else if(c != ',')
                    temp += c;
            }
            AddText(x, y + (0.5 * rayon), indice, col);
        }
    }
}

void Svgfile::AddArete(double x1, double y1, double x2, double y2, double rayon, double rayon2, std::string couleur, double width, bool ponderation, double poids, bool oriente, int id, bool draw_text)
{
    double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    double dirX = (x2 - x1) / distance;
    double dirY = (y2 - y1) / distance;
    x1 += dirX*rayon;
    y1 += dirY*rayon;
    if(rayon2 == -1)
    {
        x2 -= dirX*rayon;
        y2 -= dirY*rayon;
    }
    else
    {
        x2 -= dirX*rayon2;
        y2 -= dirY*rayon2;
    }

    AddLine(x1, y1, x2, y2, couleur, width);
    if(draw_text)
    {
        AddRectangle((x1 + x2) / 2 - 12,((y1 + y2) / 2) - 14, 24, 28, "white", 1, "black");
        AddText((x1 + x2) / 2,(y1 + y2) / 2, id, "black");

        if(ponderation)
        {
            if(x1!=x2)
                AddText((x1 + x2) / 2,((y1 + y2) / 2) + 25, poids, "purple");
            else
                AddText(((x1 + x2) / 2) + 20,(y1 + y2) / 2, poids, "purple");
        }
    }
    distance = 20;
    if(oriente)
        AddTriangle(x2, y2,
                    x2 - distance * dirX - distance / 2 * dirY,
                    y2 - distance * dirY - distance / 2 * (-dirX),
                    x2 - distance * dirX + distance / 2 * dirY,
                    y2 - distance * dirY + distance / 2 * (-dirX),
                    couleur);
}

std::string Svgfile::MakeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
