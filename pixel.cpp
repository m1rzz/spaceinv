#include "pixel.hpp"

Pixel::Pixel(Vector2 pos)
{
    this -> pos = pos;
}

void Pixel::Draw()
{
    DrawRectangle(pos.x, pos.y, 3, 3, {243, 216, 63, 255});
}
