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
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 20; ++j)
            data[i][j] = ' ';

    // Clear trails
    for (int i = 1; i <= 7; ++i)
        clear(i);

    // Clear corner trails
    data[0][0] = '-';
    data[0][9] = '-';
    data[3][0] = '-';
    data[3][9] = '-';
    data[0][19] = '-';
    data[3][19] = '-';
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
    data[1][0] = c;
    data[2][0] = c;
}

void Display::paintT2(char c)
{
    for (int i = 1; i < 9; ++i)
        data[0][i] = c;
}

void Display::paintT3(char c)
{
    data[1][9] = c;
    data[2][9] = c;
}

void Display::paintT4(char c)
{
    for (int i = 1; i < 9; ++i)
        data[3][i] = c;
}

void Display::paintT5(char c)
{
    for (int i = 10; i < 19; ++i)
        data[0][i] = c;
}

void Display::paintT6(char c)
{
    data[1][19] = c;
    data[2][19] = c;
}

void Display::paintT7(char c)
{
    for (int i = 10; i < 19; ++i)
        data[3][i] = c;
}

