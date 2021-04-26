#ifndef BOOTANIMATION_H
#define BOOTANIMATION_H

#include "RenderObject.h"
#include "bitmaps.h"

class BootAnimationRenderer : public RenderObject
{
    public:
        BootAnimationRenderer(Adafruit_SSD1306& display):
            RenderObject(display), current_frame(-1) {}
        void render(u_long delta);
        bool finished() const override { return current_frame >= frame_count; }
    protected:
        void draw();
    private:
        const uint16_t frame_count = 4;
        const uint8_t* frames[4] = {
            bitmap_bootLogo1, bitmap_bootLogo2,
            bitmap_bootLogo3, bitmap_bootLogo4
            };
        const uint16_t display_times[4] = {500, 1000, 1500, 2500};
        int current_frame;
};

#endif