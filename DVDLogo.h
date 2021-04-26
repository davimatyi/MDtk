#ifndef DVDLogo_H
#define DVDLogo_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"


class DVDLogo {
    public:
        DVDLogo(Adafruit_SSD1306 &display): display(display), totalTime(0), prevSec(0) {};
        void render(u_long delta);
    private:
        Adafruit_SSD1306 &display;
        int16_t calcX(float time);
        int16_t calcY(float time);
        u_long totalTime;
        u_long prevSec;
};



#endif