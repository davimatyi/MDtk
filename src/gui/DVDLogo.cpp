#include "DVDLogo.h"
#include "bitmaps.h"

void DVDLogo::draw() {
    display.clearDisplay();
    display.drawBitmap(currentX, currentY, bitmap_dvdLogo, 32, 16, WHITE);
    display.display();
}

void DVDLogo::render(u_long delta) {
    elapsedTime += delta;
    if(elapsedTime > frame_time) {
        currentX += velocityX;
        currentY += velocityY;
        if(currentX + LOGO_WIDTH == screen_width) velocityX = -velocityX;
        if(currentY + LOGO_HEIGHT == screen_height) velocityY = -velocityY;
        if(currentX == 0) velocityX = -velocityX;
        if(currentY == 0) velocityY = -velocityY;
        draw();
        elapsedTime = 0;
    }
}