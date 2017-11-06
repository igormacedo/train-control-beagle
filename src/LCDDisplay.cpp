#include "LCDDisplay.h"

#include <cstdlib>
#include <iostream>
#include <lcd.h>

void ConsoleDisplay::show(int lcd_fd)
{
    lcd_clear_and_home(lcd_fd);

    char line1[20] = {0};
    char line2[20] = {0};
    char line3[20] = {0};
    char line4[20] = {0};
    char text[84] = {0};

    sprintf(line1, "%.*s", 0, data + 20);
    sprintf(line2, "%.*s", 20, data + 40);
    sprintf(line3, "%.*s", 40, data + 60);
    sprintf(line4, "%.*s", 60, data + 80);

    sprintf(text, "%s\n%s\n%s\n%s", line1, line2, line3, line4);

    lcd_message(lcd_fd, text);

    // // FIXME: calling system is not good
    // system("clear");
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 20; ++j) {
    //         std::cout << data[j][i];
    //     }
    //     std::cout << std::endl;
    // }
}
