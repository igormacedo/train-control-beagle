#include "ConsoleDisplay.h"

#include <cstdlib>
#include <iostream>

void ConsoleDisplay::show()
{
    // FIXME: calling system is not good
    system("clear");
    for (int i = 0; i < 4; ++i)
        std::cout << data[i] << std::endl;
}
