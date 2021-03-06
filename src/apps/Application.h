#ifndef APPLICATION_H
#define APPLICATION_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

class Application
{
    public:
        Application(Adafruit_SSD1306& display):
            display(display), elapsed_time(0), screen_width(display.width()), screen_height(display.height()) {}
        virtual void tick(u_long delta);
    protected:
        virtual void draw();
        
    protected:
        Adafruit_SSD1306& display;
        const float frame_time = 1.f / 60.f;
        float elapsed_time;
        const u_int16_t screen_width;
        const u_int16_t screen_height;

};


#endif