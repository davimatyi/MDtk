#include "Settings.h"

void Settings::tick(u_long delta)
{
    draw();
}

void Settings::draw()
{
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Settings");
    display.display();
}