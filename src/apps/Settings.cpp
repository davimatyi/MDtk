#include "Settings.h"

void Settings::tick(u_long delta)
{
    if((*input_matrix)[1][2]) --selection;
    if((*input_matrix)[3][2]) ++selection;
    if(selection < 0) selection = 0;
    if(selection > 3) selection = 3;
    if((*input_matrix)[2][2]) 
    {
        // TODO enter submenu
        if(settingsItems[selection].value)
        {
            if(settingsItems[selection].type == SET_CHECKBOX) 
                *(settingsItems[selection].value) = ! *(settingsItems[selection].value);
        }
    }
    destY = selection * 16;
    elapsed_time += delta;

    if(elapsed_time > frame_time)
    {
        currentY += abs(destY - currentY) > 2 ? (destY - currentY) / 2 : destY - currentY;
        draw();
        elapsed_time = 0;
    }
}

void Settings::draw()
{
    display.setTextSize(1);
    display.clearDisplay();
    display.fillRect(16, 16, 112, 16, WHITE);
    for(int i = 0; i < 4; ++i)
    {
        uint16_t color = i != selection ? WHITE : BLACK;
        if(settingsItems[i].type == SET_CHECKBOX) 
        {
            if(*settingsItems[i].value)
                display.drawBitmap(0, 16 - currentY + i * 16, bitmap_checkbox_checked, 16, 16, color, 1 - color);
            else
                display.drawBitmap(0, 16 - currentY + i * 16, bitmap_checkbox_unchecked, 16, 16, color, 1 - color);
        } else
        {
            // TODO draw something for submenus
        }
        display.setCursor(18, 16 - currentY + i * 16 + 4);
        display.setTextColor(color);
        display.print(settingsItems[i].text);
    }
    display.display();
}