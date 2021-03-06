#ifndef DVDLogo_H
#define DVDLogo_H

#include "Application.h"

class DVDLogo : public Application
{
    public:
        DVDLogo(Adafruit_SSD1306& display, bool& screensaver):
            Application(display), currentX(0), currentY(10), velocityX(1), velocityY(1), animate(screensaver) {}
        void tick(u_long delta) override;
    protected:
        void draw() override;
    private:
        const int16_t LOGO_WIDTH = 32;
        const int16_t LOGO_HEIGHT = 16;
        int16_t currentX;
        int16_t currentY;
        int16_t velocityX;
        int16_t velocityY;
        bool& animate;
};


#endif