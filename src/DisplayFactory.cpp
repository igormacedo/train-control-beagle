#include "DisplayFactory.h"

Display* DisplayFactory::getDisplay(Display::DisplayType type)
{
    switch (type) {
    case Display::CONSOLE:
        return new ConsoleDisplay;
    default:
        return 0;
    }
}
