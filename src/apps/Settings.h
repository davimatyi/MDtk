#ifndef SETTINGS_H
#define SETTINGS_H

#include "Application.h"
#include "../gui/bitmaps.h"

enum SettingType { SET_CHECKBOX, SET_SUBMENU };
struct SettingsItem
{
    int index;
    SettingType type;
    const char* text;
    bool* value;
};

class Settings : public Application
{
    public:
        Settings(Adafruit_SSD1306& display, bool (*input)[5][5], bool* dvdlogo):
            Application(display), currentY(0), destY(0), selection(0), input_matrix(input), dvdlogo_enabled(dvdlogo) {}
        void tick(u_long delta);
        bool* dvdlogo_enabled;
    protected:
        void draw();

    private:
        SettingsItem settingsItems[4] = 
        {
            {0, SET_CHECKBOX, "DVD logo", dvdlogo_enabled},
            {1, SET_SUBMENU, "Szia Lajos"},
            {2, SET_SUBMENU, "XD"},
            {3, SET_CHECKBOX, "Amogus"}
        };
        bool (*input_matrix)[5][5];
        int selection = 0;
        int currentY;
        int destY;
        const float frame_time = 1.f / 30.f;
};

#endif