using namespace std;
#include <iostream>
#include "game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update()
{
    for (auto& laser: spaceship.lasers)
    {
        laser.Update();
    }   

    DeleteLasers();
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
        laser.Draw();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT)) 
        spaceship.MoveLeft();
    else if (IsKeyDown(KEY_RIGHT)) 
        spaceship.MoveRight();
    else if (IsKeyDown(KEY_SPACE))
        spaceship.FireLaser();
}

void Game::DeleteLasers()
{
    for (auto iterator = spaceship.lasers.begin(); iterator != spaceship.lasers.end();)
    {
        if (!iterator -> active)
            iterator = spaceship.lasers.erase(iterator);
        else 
            ++iterator;
    }
}
