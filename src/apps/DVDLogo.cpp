#include "DVDLogo.h"
#include "../gui/bitmaps.h"

void DVDLogo::draw() 
{
    display.clearDisplay();
    display.drawBitmap(currentX, currentY, bitmap_dvdLogo, 32, 16, WHITE);
    display.display();
}

int16_t sign(int16_t x) 
{
    return (x > 0) - (x < 0);
}

void DVDLogo::tick(u_long delta) 
{
    if(!animate) return;
    elapsed_time += delta;
    if(elapsed_time > frame_time) 
    {
        currentX += velocityX;
        currentY += velocityY;
        if(currentX + LOGO_WIDTH == screen_width) velocityX = -velocityX;
        if(currentY + LOGO_HEIGHT == screen_height) velocityY = -velocityY;
        if(currentX == 0) velocityX = -sign(velocityX) * (rand() % 2 + 1);
        if(currentY == 0) velocityY = -sign(velocityY) * (rand() % 2 + 1);
        draw();
        elapsed_time = 0;
    }
}