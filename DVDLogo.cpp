#include "DVDLogo.h"

int16_t DVDLogo::calcX(float time) {
    float mult = (sin(time * (2 * M_PI / 10.f)) + 1) / 2.f;
    return (int16_t) (mult * 96);
}

int16_t DVDLogo::calcY(float time) {
    float mult = (sin(time * (2 * M_PI / 2.f)) + 1) / 2.f;
    return (int16_t) (mult * 48);
}

void DVDLogo::render(u_long delta) {
    totalTime += delta;
    display.clearDisplay();
    display.drawBitmap(calcX(totalTime / 1000.f), calcY(totalTime / 1000.f), dvdLogo, 32, 16, WHITE);
    display.display();

}
