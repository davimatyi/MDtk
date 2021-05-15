#ifndef MENU_H
#define MENU_H

#include "Application.h"
#include "../gui/bitmaps.h"

enum MODE { MODE_MENU, MODE_KEYBOARD, MODE_MACRO, MODE_CALCULATOR, MODE_SETTINGS, MODE_DOOM };

#define MENUITEM_COUNT 5
struct MenuItem
{
    int index;
    const uint8_t* bitmap;
    MODE mode;
    const char* text;
    int text_len;
};

class Menu : public Application
{
    public:
        Menu(Adafruit_SSD1306& display, bool (*input)[5][5]):
            Application(display), currentX(0), destX(0), selection(0), input_matrix(input) {}
        void tick(u_long delta);
        bool finished() const override {return false;}
    private:
        void draw();

    private:
        MenuItem menuItems[MENUITEM_COUNT] = 
        {
            { 0, bitmap_menuItem_keyboard, MODE_KEYBOARD, "Keyboard", 8 },
            { 1, bitmap_menuItem_macro, MODE_MACRO, "Macro", 5 },
            { 2, bitmap_menuItem_calculator, MODE_CALCULATOR, "Calc", 4 },
            { 3, bitmap_menuItem_settings, MODE_SETTINGS, "Settings", 8 },
            { 4, bitmap_menuItem_doom, MODE_DOOM, "Doom", 4 }
        };
        bool (*input_matrix)[5][5];
        int currentX;
        int destX;
        int selection;
        const float frame_time = 1.f / 30.f;
    
};

#endif