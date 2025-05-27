#include <iostream>
#include "laser.hpp"

using namespace std;

Laser :: Laser (Vector2 pos, int speed)
{
    this -> pos = pos;
    this -> speed = speed;
    
    active = true;
}

void Laser :: Draw()
{
    if (active)
        DrawRectangle(pos.x, pos.y, 
        4, 15, {243, 216, 63, 255});
}

Rectangle Laser :: getRect()
{
    Rectangle rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.width = 4;
    rect.height = 15;

    return rect;
}

void Laser :: Update()
{
    pos.y += speed;

    if (active)
    {
        if (pos.y > GetScreenHeight() - 100 || pos.y < 25)
            active = false;
    }
}