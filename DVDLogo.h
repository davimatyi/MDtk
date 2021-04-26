#ifndef DVDLogo_H
#define DVDLogo_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


class DVDLogo {
    public:
        DVDLogo(Adafruit_SSD1306 &display): display(display), elapsedTime(0), currentX(0), currentY(10), velocityX(1), velocityY(1) {};
        void render(u_long delta);
    private:
        Adafruit_SSD1306 &display;
        const int16_t LOGO_WIDTH = 32;
        const int16_t LOGO_HEIGHT = 16;
        const float FRAME_TIME = 1.f / 60.f; // 60 fps
        float elapsedTime;
        int16_t currentX;
        int16_t currentY;
        int16_t velocityX;
        int16_t velocityY;

        void draw();
};



#endif