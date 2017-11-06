#ifndef DISPLAYFACTORY_H
#define DISPLAYFACTORY_H

#include "ConsoleDisplay.h"
#include "LCDDisplay.h"
#include "Display.h"

class DisplayFactory {
public:
    static Display* getDisplay(Display::DisplayType type);
};

#endif
