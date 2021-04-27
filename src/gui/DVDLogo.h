#ifndef DVDLogo_H
#define DVDLogo_H

#include "RenderObject.h"

class DVDLogo : public RenderObject
{
    public:
        DVDLogo(Adafruit_SSD1306& display):
            RenderObject(display), currentX(0), currentY(10), velocityX(1), velocityY(1) {}
        void render(u_long delta) override;
        bool finished() const override { return false; }
    protected:
        void draw() override;
    private:
        const int16_t LOGO_WIDTH = 32;
        const int16_t LOGO_HEIGHT = 16;
        float elapsedTime;
        int16_t currentX;
        int16_t currentY;
        int16_t velocityX;
        int16_t velocityY;
};


#endif