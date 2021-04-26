#ifndef MENURENDERER_H
#define MENURENDERER_H

#include "RenderObject.h"

class MenuRenderer : public RenderObject
{
    public:
        MenuRenderer(Adafruit_SSD1306& display):
            RenderObject(display) {}
        void render(u_long delta);
        void draw();
    
};

#endif