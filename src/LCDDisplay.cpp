#include "LCDDisplay.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "lcd.h"

LCDDisplay::LCDDisplay()
{
    lcd_fd = lcd_open("/dev/lcd0");
}

void LCDDisplay::show()
{
    lcd_clear_and_home(lcd_fd);

    for (int i = 0; i < 4; ++i){
        lcd_message(lcd_fd, "%s", data[i]);
    }
}
