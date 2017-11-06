#ifndef DISPLAY_H
#define DISPLAY_H

//  The display consists of a 20x4 matrix that is painted to simulate
//  two trains.
//
//  The trail numbers are organized as follows:
//
//  -22222222-555555555-
//  1        3         6
//  1        3         6
//  -44444444-777777777-
//
//  An example of the display painted (trails 1 and 6)
//
//  -oooooooo-----------
//  |        |         x
//  |        |         x
//  --------------------

#include <map>

class Display {
public:
    typedef void (Display::*MFP)(char);
    int lcd_fd;

    Display();

    enum DisplayType {
        CONSOLE,
        LCD
    };

    void fill(int trail, char c);
    void clear(int trail);

    void paintT1(char symbol);
    void paintT2(char symbol);
    void paintT3(char symbol);
    void paintT4(char symbol);
    void paintT5(char symbol);
    void paintT6(char symbol);
    void paintT7(char symbol);

    virtual void show() = 0;

protected:
    char data[4][20];

private:
    std::map<int, MFP> paintFunctions;
};

#endif
