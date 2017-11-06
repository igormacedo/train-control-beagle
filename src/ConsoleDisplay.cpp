#include "ConsoleDisplay.h"

#include <iostream>

void ConsoleDisplay::show()    
{
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 20; ++j) {
            std::cout << data[j][i];
        }
        std::cout << std::endl;
    } 
}
