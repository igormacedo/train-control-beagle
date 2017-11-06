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
    lcd_message(lcd_fd, "%s%s%s%s", data[0],data[1],data[2],data[3]);
}
