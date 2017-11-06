#include "ConsoleDisplay.h"

#include <cstdlib>
#include <iostream>

void ConsoleDisplay::show()
{
    // FIXME: calling system is not good
    system("clear");
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 20; ++j) {
            std::cout << data[j][i];
        }
        std::cout << std::endl;
    }
}
