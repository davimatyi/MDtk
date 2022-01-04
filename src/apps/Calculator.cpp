#include "Calculator.h"

void Calculator::tick(u_long delta)
{
    for(int i = 0; i < 5; ++i) 
    {
        for(int j = 0; j < 5; ++j) 
        {
            if((*input_matrix)[j][i]) 
            {
                if(solve) solve = false;
                if(i == 4 && j == 3) 
                {
                    
                    bool err = false;
                    int res = 0;
                    result = std::to_string(res);
                    solve = true;
                } else
                {
                    expr.push_back(SYMBOLS[j][i]);
                }

            }
        }
    }
    elapsed_time += delta;

    if(elapsed_time > frame_time)
    {
        draw();
        elapsed_time = 0;
    }
    
}

void Calculator::draw()
{
    display.clearDisplay();

    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("c");
    display.print(expr.c_str());


    if(solve) {
        display.setTextSize(2);
        display.setCursor(128 - result.length() * 16, 48);
        display.print(result.c_str());
    }

    display.display();
}