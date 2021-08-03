#ifndef SETTINGS_H
#define SETTINGS_H

#include "Application.h"

class Settings : public Application
{
    public:
        Settings(Adafruit_SSD1306& display):
            Application(display) {}
        void tick(u_long delta);
    protected:
        void draw();
};

#endif