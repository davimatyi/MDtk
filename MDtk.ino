#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Keyboard.h>

#include "bitmaps.h"


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

const char KEYS[5][5] = {
    {'M', 219, 220, 221, 222},
    {'A', 231, 232, 233, 223},
    {'B', 228, 229, 230, ' '},
    {'C', 225, 226, 227, 224},
    {'D', 234, ' ', 235, ' '}
    
};

bool PREV_KEYSTATE[5][5] = {false};
bool PRESSED_KEYS[5][5] = {false};

const unsigned char KEY_ROWPINS[5] = {
    PB1, PB0, PA3, PA2, PA1
};

const unsigned char KEY_COLPINS[5] = {
    PB14, PB15, PA15, PB3, PB5
};

enum MODE { MODE_KEYBOARD, MODE_MACRO, MODE_CALCULATOR, MODE_MENU, MODE_DOOM };
MODE CURRENTMODE = MODE_KEYBOARD;
MODE PREV_MODE = MODE_MENU;

#pragma endregion


void setup() {
    pinMode(LED_ONBOARD, OUTPUT);
    digitalWrite(LED_ONBOARD, HIGH);
    Keyboard.begin();

    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("Display communication failed");
        for(;;);
    }

    for(int i = 0; i < 5; ++i) {
        pinMode(KEY_ROWPINS[i], INPUT_PULLDOWN);
        pinMode(KEY_COLPINS[i], OUTPUT);
        digitalWrite(KEY_COLPINS[i], HIGH);
    }

    showBootUpLogo();
}

void loop() {

    // scanning button matrix
    for(int i = 0; i < 5; ++i) {
        digitalWrite(KEY_COLPINS[i], HIGH);
        for(int j = 0; j < 5; ++j) {
            PRESSED_KEYS[j][i] = false;
            if(digitalRead(KEY_ROWPINS[j])) {
                if(!PREV_KEYSTATE[j][i]) {
                    PREV_KEYSTATE[j][i] = true;
                    PRESSED_KEYS[j][i] = true;
                    if(CURRENTMODE == MODE_KEYBOARD && i > 0)
                        Keyboard.press(KEYS[j][i]);
                }
            } else {
                if(PREV_KEYSTATE[j][i]) {
                    PREV_KEYSTATE[j][i] = false;
                    if(CURRENTMODE == MODE_KEYBOARD && i > 0)
                        Keyboard.release(KEYS[j][i]);
                }
            }
        }
        digitalWrite(KEY_COLPINS[i], LOW);
    }

    //BUG this freezes for some reason
    //if(PRESSED_KEYS[0][0]) toggleMenu();

    
    
}

void showBootUpLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, bootLogo1, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.drawBitmap(0, 0, bootLogo2, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.drawBitmap(0, 0, bootLogo3, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.drawBitmap(0, 0, bootLogo4, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
    display.display();
    delay(3000);
    display.clearDisplay();
    display.display();
}

void drawMenu() {
    display.setTextSize(2);
    display.setCursor(10,10);
    display.print("Menu");
    display.display();
}

void toggleMenu() {
    if(CURRENTMODE != MODE_MENU) {
        PREV_MODE = CURRENTMODE;
        CURRENTMODE = MODE_MENU;
        drawMenu();
    } else {
        CURRENTMODE = PREV_MODE;
        PREV_MODE = MODE_MENU;
        display.clearDisplay();
        display.display();
    }
}
