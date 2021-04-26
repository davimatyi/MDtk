#include "DVDLogo.h"

void DVDLogo::draw() {
    display.clearDisplay();
    display.drawBitmap(currentX, currentY, dvdLogo, 32, 16, WHITE);
    display.display();
}

void DVDLogo::render(u_long delta) {
    elapsedTime += delta;
    if(elapsedTime > FRAME_TIME) {
        currentX += velocityX;
        currentY += velocityY;
        if(currentX + LOGO_WIDTH == SCREEN_WIDTH) velocityX = -velocityX;
        if(currentY + LOGO_HEIGHT == SCREEN_HEIGHT) velocityY = -velocityY;
        if(currentX == 0) velocityX = -velocityX;
        if(currentY == 0) velocityY = -velocityY;
        draw();
        elapsedTime = 0;
    }
}
