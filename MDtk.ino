#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keyboard.h>

#include "src/apps/Application.h"
#include "src/apps/BootAnimation.h"
#include "src/apps/DVDLogo.h"
#include "src/apps/Menu.h"
#include "src/apps/Settings.h"
#include "src/apps/Calculator.h"

#pragma region DEFINES

#define LED_ONBOARD PC13
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#pragma endregion

#pragma region INITIALIZATIONS

TwoWire Wire2(PB9, PB8);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, -1);

#pragma endregion

#pragma region VARIABLES

const char KEYS[5][5] = 
{
    {'M', 219, 220, 221, 222},
    {'A', 231, 232, 233, 223},
    {'B', 228, 229, 230, ' '},
    {'C', 225, 226, 227, 224},
    {'D', 234, ' ', 235, ' '}
    
};

bool PREV_KEYSTATE[5][5] = {false};
bool PRESSED_KEYS[5][5] = {false};

const unsigned char KEY_ROWPINS[5] = 
{
    PB1, PB0, PA3, PA2, PA1
};

const unsigned char KEY_COLPINS[5] = 
{
    PB14, PB15, PA15, PB3, PB5
};

MODE CURRENTMODE = MODE_KEYBOARD;
MODE PREV_MODE = MODE_MENU;

Application* app_instances[MENUITEM_COUNT];
BootAnimation* boot_animation_instance;
Menu* menu_instance;

bool screenSaver = false;

u_long previous_time = millis();

#pragma endregion


void setup() 
{
    srand((int) millis());
    pinMode(LED_ONBOARD, OUTPUT);
    digitalWrite(LED_ONBOARD, HIGH);
    Keyboard.begin();

    Serial.begin(9600);

    Serial.write("setup()");

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) 
    {
        Serial.println("Display communication failed");
        for(;;);
    }

    for(int i = 0; i < 5; ++i) 
    {
        pinMode(KEY_ROWPINS[i], INPUT_PULLDOWN);
        pinMode(KEY_COLPINS[i], OUTPUT);
        digitalWrite(KEY_COLPINS[i], HIGH);
    }

    boot_animation_instance = new BootAnimation(display);
    menu_instance = new Menu(display, &PRESSED_KEYS);


    // TODO instantiate these when they exist
    app_instances[0] = new DVDLogo(display, screenSaver); // keyboard
    app_instances[1] = nullptr; // macropad
    app_instances[2] = new Calculator(display, &PRESSED_KEYS); // calculator
    app_instances[3] = new Settings(display, &PRESSED_KEYS, &screenSaver); // settings
    app_instances[4] = nullptr; // doom
}


void loop() 
{
    u_long current_time = millis();
    u_long delta_time = current_time - previous_time;

    

    // scanning button matrix
    for(int i = 0; i < 5; ++i) 
    {
        digitalWrite(KEY_COLPINS[i], HIGH);

        for(int j = 0; j < 5; ++j) 
        {
            PRESSED_KEYS[j][i] = false;

            if(digitalRead(KEY_ROWPINS[j])) 
            {
                if(!PREV_KEYSTATE[j][i]) 
                {
                    PREV_KEYSTATE[j][i] = true;
                    PRESSED_KEYS[j][i] = true;

                    if(CURRENTMODE == MODE_KEYBOARD && i > 0)
                        Keyboard.press(KEYS[j][i]);
                }

            } else 
            {
                if(PREV_KEYSTATE[j][i]) 
                {
                    PREV_KEYSTATE[j][i] = false;

                    if(CURRENTMODE == MODE_KEYBOARD && i > 0)
                        Keyboard.release(KEYS[j][i]);
                }
            }
        }
        digitalWrite(KEY_COLPINS[i], LOW);
    }

    // boot animation still going, disable menu and other apps
    if(!boot_animation_instance->finished()) 
    {
        boot_animation_instance->tick(delta_time);
    } else
    {
        // top left 'menu' key pressed
        if(PRESSED_KEYS[0][0]) toggleMenu();

        // if user is in menu, render it
        if(CURRENTMODE == MODE_MENU) 
        {
            menu_instance->tick(delta_time);
            // an app is selected
            if(PRESSED_KEYS[2][2]) 
            {
                CURRENTMODE = menu_instance->current_mode();
                PREV_MODE = MODE_MENU;
                display.clearDisplay();
                display.display();
            }
        }
        // an app other than the menu will be rendered
        else
        {
            if(app_instances[menu_instance->app_index] != nullptr)
            {
                app_instances[menu_instance->app_index]->tick(delta_time);
            }
        }
    }


    previous_time = current_time;
}


void toggleMenu() 
{
    if(CURRENTMODE == MODE_MENU) 
    {
        CURRENTMODE = PREV_MODE;
        PREV_MODE = MODE_MENU;
        display.clearDisplay();
        display.display();
    } else 
    {
        PREV_MODE = CURRENTMODE;
        CURRENTMODE = MODE_MENU;
        menu_instance->resetSelection();
    }
}
