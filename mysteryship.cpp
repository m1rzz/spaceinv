#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture ("Graphics/mystery.png");
    alive = false;
}

MysteryShip :: ~MysteryShip()
{
    UnloadTexture (image);
}

void MysteryShip :: Spawn()
{
    int side = GetRandomValue (0, 1);
    pos.y = 90;

    if (side == 0)
    {
        pos.x = 0;
        speed = 3;
    } else 
    {
        pos.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    alive = true;

}

Rectangle MysteryShip :: getRect()
{
    if (alive)
        return {pos.x, pos.y, 
        float (image.width), 
        float (image.height)};
     else 
        return {pos.x, pos.y, 0, 0};
}

void MysteryShip :: Update()
{
    if (alive)
    {
        pos.x += speed;

        if (pos.x > GetScreenWidth() - image.width || pos.x < 0)
            alive = false;
    }
}

void MysteryShip :: Draw()
{
    if (alive)
        DrawTextureV (image, pos, WHITE);
}