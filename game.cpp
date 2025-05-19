using namespace std;
#include <iostream>
#include "game.hpp"

Game::Game()
{
    barriers = CreateBarrier();
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
    {
        laser.Draw();
    }

    for (auto& barrier : barriers)
        barrier.Draw();
}

void Game::HandleInput()
{
    if (IsKeyDown (KEY_LEFT) ) 
        spaceship.MoveLeft();
    else if (IsKeyDown (KEY_RIGHT) ) 
        spaceship.MoveRight();
    else if (IsKeyDown (KEY_SPACE) )
        spaceship.FireLaser();
}

void Game::DeleteLasers()
{
    for (auto iterator = spaceship.lasers.begin(); iterator != spaceship.lasers.end();)
    {
        if (!iterator -> active)
            iterator = spaceship.lasers.erase (iterator);
        else 
            ++iterator;
    }
}

vector <Barrier> Game::CreateBarrier()
{
    int barrierWidth = Barrier::grid[0].size() * 3;
    float gaps = (GetScreenWidth() - (4 * barrierWidth)) / 3;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = i * gaps + (barrierWidth * 1.5f);
        barriers.push_back (Barrier ({offsetX, 
            float (GetScreenHeight() - 100)}));
    }
    
    return barriers;
}
