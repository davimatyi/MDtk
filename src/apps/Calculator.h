#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Application.h"

const char SYMBOLS[5][5] = 
{
    {' ', '%', '/', '*', '-'},
    {'(', '7', '8', '9', '+'},
    {')', '4', '5', '6', ' '},
    {'<', '1', '2', '3', '='},
    {'>', '0', ' ', '&', ' '}  
};

class Calculator : public Application
{
    public:
        Calculator(Adafruit_SSD1306& display, bool (*input)[5][5]):
            Application(display), input_matrix(input), solve(false) {}
        void tick(u_long delta);
    protected:
        void draw();

    private:
        bool (*input_matrix)[5][5];
        std::string expr;
        std::string result;
        bool solve;
        
};

#endif