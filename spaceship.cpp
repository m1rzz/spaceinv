#include "spaceship.hpp"

Spaceship :: Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    pos.x = (GetScreenWidth() - image.width) / 2;
    pos.y = GetScreenHeight() - image.height;

    lastShotTime = 0.0;
}

Spaceship :: ~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTextureV (image, pos, WHITE);
}

void Spaceship :: MoveLeft()
{
    pos.x -= 7;

    if (pos.x < 0) 
        pos.x = 0;
}

void Spaceship :: MoveRight()
{
    pos.x += 7;

    if (pos.x > GetScreenWidth() - image.width) 
        pos.x = GetScreenWidth() - image.width;
}

void Spaceship :: FireLaser()
{
    if (GetTime() - lastShotTime >= 0.35)
    {
        lasers.push_back(Laser
        ({(pos.x + image.width / 2) - 2, pos.y}, -6));
        lastShotTime = GetTime();
    }

}

Rectangle Spaceship :: getRect()
{
    return {pos. x, pos.y, 
    float (image.width), 
    float (image.height)};
}

void Spaceship :: Reset()
{
    pos.x = (GetScreenWidth() - image.width) / 2.0f;
    pos.y = GetScreenHeight() - image.height;
    lasers.clear();
}