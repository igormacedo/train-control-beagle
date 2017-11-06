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
//  |        |         o
//  |        |         o
//  --------------------

class Display {
public:
    typedef void (Display::*MFP)();

    Display();

    enum DisplayType {
        CONSOLE,
        LCD
    };

    void paint(int trail);
    void clear(int trail);
    
    virtual void show() = 0;

protected:
    char data[20][4];
};

#endif
