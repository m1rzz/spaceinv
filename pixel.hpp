#pragma once
#include <raylib.h>

class Pixel
{
    public:

        Pixel(Vector2 pos);
        Rectangle getRect();
        void Draw();

    private:
    
        Vector2 pos;
};