#include "spaceship.hpp"

Spaceship :: Spaceship()
{
    image = LoadTexture ("Graphics/spaceship.png");
    pos.x = (GetScreenWidth() - image.width) / 2;
    pos.y = GetScreenHeight() - image.height - 100;

    lastShotTime = 0.0;
    laserSound = LoadSound ("Sounds/laser.ogg");
}

Spaceship :: ~Spaceship()
{
    UnloadTexture (image);
    UnloadSound (laserSound);
}

void Spaceship :: Draw()
{
    DrawTextureV (image, pos, WHITE);
}

void Spaceship :: MoveLeft()
{
    pos.x -= 7;

    if (pos.x < 25) 
        pos.x = 25;
}

void Spaceship :: MoveRight()
{
    pos.x += 7;

    if (pos.x > GetScreenWidth() - image.width - 25) 
        pos.x = GetScreenWidth() - image.width - 25;
}

void Spaceship :: FireLaser()
{
    if (GetTime() - lastShotTime >= 0.35)
    {
        lasers.push_back (Laser
        ({(pos.x + image.width / 2) - 2, pos.y}, -6));

        lastShotTime = GetTime();
        PlaySound (laserSound);
    }

}

Rectangle Spaceship :: getRect()
{
    // hitbox of the spaceship 
    return {pos. x, pos.y, 
    float (image.width), 
    float (image.height)};
}

void Spaceship :: Reset()
{
    pos.x = (GetScreenWidth() - image.width) / 2.0f;
    pos.y = GetScreenHeight() - image.height - 100;

    lasers.clear();
}