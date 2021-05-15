#ifndef MENU_H
#define MENU_H

#include "Application.h"

enum MODE { MODE_KEYBOARD, MODE_MACRO, MODE_CALCULATOR, MODE_MENU, MODE_DOOM };

class Menu : public Application
{
    public:
        Menu(Adafruit_SSD1306& display):
            Application(display) {}
        void tick(u_long delta);
        bool finished() const override {return false;}
    private:
        void draw();
    
};

#endif