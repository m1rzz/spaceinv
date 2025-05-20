#pragma once
#include <raylib.h>

class Pixel
{
    public:

        Pixel(Vector2 pos);
        void Draw();
        Rectangle getRect();

    private:
    
        Vector2 pos;
};