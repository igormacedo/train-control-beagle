#include "Display.h"

#include <iostream>

Display::Display()
{
    // Initialize paint functions
    paintFunctions[1] = &Display::paintT1;
    paintFunctions[2] = &Display::paintT2;
    paintFunctions[3] = &Display::paintT3;
    paintFunctions[4] = &Display::paintT4;
    paintFunctions[5] = &Display::paintT5;
    paintFunctions[6] = &Display::paintT6;
    paintFunctions[7] = &Display::paintT7;

    // Clear display
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 4; ++j)
            data[i][j] = ' ';

    // Clear trails
    for (int i = 1; i <= 7; ++i)
        clear(i);

    // Clear corner trails
    data[0][0] = '-';
    data[9][0] = '-';
    data[0][3] = '-';
    data[9][3] = '-';
    data[19][0] = '-';
    data[19][3] = '-';
}

void Display::fill(int trail, char c)
{
    (this->*paintFunctions[trail])(c);
}

void Display::clear(int trail)
{
    switch (trail) {
    case 1:
    case 3:
    case 6:
        (this->*paintFunctions[trail])('|');
        break;
    case 2:
    case 4:
    case 5:
    case 7:
        (this->*paintFunctions[trail])('-');
        break;
    }
}

void Display::paintT1(char c)
{
    data[0][1] = c;
    data[0][2] = c;
}

void Display::paintT2(char c)
{
    for (int i = 1; i < 9; ++i)
        data[i][0] = c;
}

void Display::paintT3(char c)
{
    data[9][1] = c;
    data[9][2] = c;
}

void Display::paintT4(char c)
{
    for (int i = 1; i < 9; ++i)
        data[i][3] = c;
}

void Display::paintT5(char c)
{
    for (int i = 10; i < 19; ++i)
        data[i][0] = c;
}

void Display::paintT6(char c)
{
    data[19][1] = c;
    data[19][2] = c;
}

void Display::paintT7(char c)
{
    for (int i = 10; i < 19; ++i)
        data[i][3] = c;
}

