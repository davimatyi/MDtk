#ifndef BOOTANIMATION_H
#define BOOTANIMATION_H

#include "Application.h"
#include "../gui/bitmaps.h"

class BootAnimation : public Application
{
    public:
        BootAnimation(Adafruit_SSD1306& display):
            Application(display), current_frame(-1) {}
        void tick(u_long delta);
        bool finished() const override { return current_frame >= frame_count; }
    protected:
        void draw();
    private:
        const uint16_t frame_count = 4;
        const uint8_t* frames[4] = 
        {
            bitmap_bootLogo1, bitmap_bootLogo2,
            bitmap_bootLogo3, bitmap_bootLogo4
        };
        const uint16_t display_times[4] = {500, 1000, 1500, 2500};
        int current_frame;
};

#endif