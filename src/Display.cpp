#include "Display.h"

#include <iostream>

Display::Display()
{
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

void Display::paint(int trail)
{
    switch (trail) {
    case 1:
        data[0][1] = 'o';
        data[0][2] = 'o';
        break;
    case 2:
        for (int i = 1; i < 9; ++i)
            data[i][0] = 'o';
        break;
    case 3:
        data[9][1] = 'o';
        data[9][2] = 'o';
        break;
    case 4:
        for (int i = 1; i < 9; ++i)
            data[i][3] = 'o';
        break;
    case 5:
        for (int i = 10; i < 19; ++i)
            data[i][0] = 'o';
        break;
    case 6:
        data[19][1] = 'o';
        data[19][2] = 'o';
        break;
    case 7:
        for (int i = 10; i < 19; ++i)
            data[i][0] = 'o';
        break;
    }
}

void Display::clear(int trail)
{
    switch (trail) {
    case 1:
        data[0][1] = '|';
        data[0][2] = '|';
        break;
    case 2:
        for (int i = 1; i < 9; ++i)
            data[i][0] = '-';
        break;
    case 3:
        data[9][1] = '|';
        data[9][2] = '|';
        break;
    case 4:
        for (int i = 1; i < 9; ++i)
            data[i][3] = '-';
        break;
    case 5:
        for (int i = 10; i < 19; ++i)
            data[i][0] = '-';
        break;
    case 6:
        data[19][1] = '|';
        data[19][2] = '|';
        break;
    case 7:
        for (int i = 10; i < 19; ++i)
            data[i][3] = '-';
        break;
    }
}

