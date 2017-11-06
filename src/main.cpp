#include "DisplayFactory.h"

int main(int argc, char* argv[])
{
    Display *display = DisplayFactory::getDisplay(Display::CONSOLE);

    display->paint(1);
    display->paint(5);
    display->show();

    return 0;
}
