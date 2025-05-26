#include <iostream>
#include "laser.hpp"
using namespace std;

Laser :: Laser (Vector2 pos, int speed)
{
    // konstruktur
    // zadava skorost i poziciq na lazerite
    this -> pos = pos;
    this -> speed = speed;
    
    active = true;
}

void Laser :: Draw()
{
    // risuva lazerite, koito sa within scope
    if (active)
        DrawRectangle(pos.x, pos.y, 
        4, 15, {243, 216, 63, 255});
}

Rectangle Laser :: getRect()
{
    // zadava koordinati i razmeri na lazerite
    Rectangle rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.width = 4;
    rect.height = 15;

    return rect;
}

void Laser :: Update()
{
    // iztriva lazeri koito sa out of scope
    pos.y += speed;

    if (active)
    {
        if (pos.y > GetScreenHeight() - 100 || pos.y < 25)
            active = false;
    }
}