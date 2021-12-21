#include "Menu.h"

void Menu::tick(u_long delta)
{
    if((*input_matrix)[2][1]) --selection;
    if((*input_matrix)[2][3]) ++selection;
    if(selection < 0) selection = 0;
    if(selection >= MENUITEM_COUNT) selection = 4;
    if((*input_matrix)[2][2]) app_index = selection;
    destX = selection * 42;
    
    elapsed_time += delta;
    if(elapsed_time > frame_time)
    {
        // currentX +=  * ((destX - currentX > 0) - (destX - currentX < 0));
        currentX += abs(destX - currentX) > 2 ? (destX - currentX) / 2 : destX - currentX;
        draw();
        elapsed_time = 0;
    }

}

void Menu::draw()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    if(selection > 0) display.print("<");
    display.setCursor(116, 0);
    if(selection < MENUITEM_COUNT-1) display.print(">");
    display.setCursor(64 - ((menuItems[selection].text_len / 2) * 12 + ((menuItems[selection].text_len % 2) * 6)), 0);
    display.print(menuItems[selection].text);
    for(int i = 0; i < MENUITEM_COUNT; ++i) 
    {
        uint16_t color = i == selection ? WHITE : BLACK;
        display.drawBitmap(44 - currentX + i * 42, 20, menuItems[i].bitmap, 40, 40, color, 1 - color);
    }
    display.display();
}