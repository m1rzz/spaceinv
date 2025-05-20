#pragma once
#include <raylib.h>

class Laser 
{
    public:

        Laser (Vector2 pos, int speed);
        Rectangle getRect();
        void Update();
        void Draw();
        bool active;

    private:

        Vector2 pos;
        int speed;
};