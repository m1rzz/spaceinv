#include "pixel.hpp"

Pixel::Pixel(Vector2 pos)
{
    this -> pos = pos;
}

void Pixel::Draw()
{
    DrawRectangle(pos.x, pos.y, 
    3, 3, {243, 216, 63, 255});
}

Rectangle Pixel :: getRect()
{
    Rectangle rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.width = 3;
    rect.height = 3;

    return rect;
}