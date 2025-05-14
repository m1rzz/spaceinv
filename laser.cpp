#include <iostream>
#include "laser.hpp"
using namespace std;

Laser::Laser(Vector2 pos, int speed)
{
    this -> pos = pos;
    this -> speed = speed;
    active = true;
}

void Laser::Draw()
{
    if (active)
        DrawRectangle(pos.x, pos.y, 4, 15, {243, 216, 63, 255});
}

void Laser::Update()
{
    pos.y += speed;
    if (active)
    {
        if (pos.y > GetScreenHeight() || pos.y < 0)
        {    
            active = false;
            cout << "laser out of scope" << endl;
        }
    }
}