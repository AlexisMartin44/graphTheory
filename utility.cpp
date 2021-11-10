#include "utility.h"

void ExitApplication(std::string msg)
{
    std::cout << "[ERROR] " << msg << std::endl << std::endl;
    exit(-1);
}
