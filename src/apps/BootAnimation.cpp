#include "BootAnimation.h"

void BootAnimation::tick(u_long delta)
{
    elapsed_time += delta;
    if(finished()) return;
    if(elapsed_time >= display_times[current_frame] || current_frame == -1)
    {
        ++current_frame;
        if(current_frame >= frame_count) 
        {
            display.clearDisplay();
            display.display();
        } 
        else
            draw();
    }
}

void BootAnimation::draw() 
{
    display.clearDisplay();
    display.drawBitmap(0, 0, frames[current_frame], screen_width, screen_height, WHITE);
    display.display();
}