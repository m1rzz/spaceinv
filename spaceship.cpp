#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    pos.x = (GetScreenWidth() - image.width) / 2;
    pos.y = GetScreenHeight() - image.height;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTextureV(image, pos, WHITE);
}

void Spaceship::MoveLeft()
{
    pos.x -= 7;
    if (pos.x < 0) 
        pos.x = 0;
}

void Spaceship::MoveRight()
{
    pos.x += 7;
    if (pos.x > GetScreenWidth() - image.width) 
        pos.x = GetScreenWidth() - image.width;
}