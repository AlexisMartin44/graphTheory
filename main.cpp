#include <iostream>
#include "Menu.h"

/*! \mainpage Théorie des graphes
*
* \section intro_sec Introduction
*
* As students at ECE Paris, we were asked to work on a project in C++. The theme of this week-long project was "Accessibility and vulnerability of networks". It allowed us to see how graph theory and some algorithms can be used in the study of accessibility and vulnerability of networks, in particular transport networks. We had a lot of fun during this week, and we hope you enjoy reading!
*
* \subsection about_sec The glorious team
*
 * <a href="../../img/Etienne.png" target="_blank">Étienne Desrousseaux</a> \n
 * <a href="../../img/Titouan.png" target="_blank">Titouan Lermite</a> \n
 * <a href="../../img/Alexis.png" target="_blank">Alexis Martin</a> \n
 * <a href="../../img/ing2TD08.png" target="_blank">ING2 TD08</a>
 *
 * \subsection view View the results
 *
 * <a href="../../index.html" target="_blank">Click here</a> to see the graphs of the latest results. \n
 * <a href="../../output.svg" target="_blank">Click here</a> to open the output.svg.
 *
 * \subsection classes Classes
 *
 * <a href="annotated.html">Click here</a> to go to the class list.
 *
 * \subsection color_guide Color guide
 *
 * <a href="../../img/colors_guide.jpg" target="_blank">Click here</a> to see our color gradient system. It refers to our color code for the nodes: the closer we get to the right, the more important the node’s indice is.
 *
 * \subsection more_img More images
 * Here are some graphs we created for fun, because why not :). \n
 * - <a href="../../img/output_degree_ny.svg" target="_blank">New York</a> (degree indices) \n
 * - <a href="../../img/pi.png" target="_blank">Pi</a> \n
 * - <a href="../../img/leaf.png" target="_blank">Leaf</a> \n
 * - <a href="../../img/random.png" target="_blank">Random</a> \n
 * - <a href="../../img/Etienne.png" target="_blank">Étienne Desrousseaux</a> \n
 * - <a href="../../img/Titouan.png" target="_blank">Titouan Lermite</a> \n
 * - <a href="../../img/Alexis.png" target="_blank">Alexis Martin</a> \n
 * - <a href="../../img/ing2TD08.png" target="_blank">ING2 TD08</a>
*/

int main()
{
    std::cout.precision(2);
    Menu menu;
    menu.Display();
    return 0;
}
