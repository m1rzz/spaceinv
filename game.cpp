using namespace std;
#include <iostream>
#include "game.hpp"

Game::Game()
{
    barriers = CreateBarrier();
    aliens = CreateAliens();
    lives = 3;
    alienDirection = 1;
    timeLastAlienLaser = 0.0;
    timeLastSpawn = 0.0f;
    mysteryShipSpawnInteval = GetRandomValue(10, 20);
}

Game::~Game()
{
    Alien :: UnloadImages();
}

void Game::Update()
{
    double currentTime = GetTime();
    if (currentTime - timeLastSpawn > mysteryShipSpawnInteval)
    {
        mysteryship.Spawn();
        timeLastSpawn = GetTime();
        mysteryShipSpawnInteval = GetRandomValue (10, 20);
    }

    for (auto& laser : spaceship.lasers)
        laser.Update();

    MoveAlien();
    AlienShootLaser();

    for (auto& laser : alienLaser)
        laser.Update();

    DeleteLasers();
    mysteryship.Update();
    CheckCollision();
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
        laser.Draw();

    for (auto& barrier : barriers)
        barrier.Draw();

    for (auto& alien : aliens)
        alien.Draw();

    for (auto& laser : alienLaser)
        laser.Draw();

    mysteryship.Draw();
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

    for (auto iterator = alienLaser.begin(); iterator != alienLaser.end();)
    {
        if (!iterator -> active)
            iterator = alienLaser.erase (iterator);
        else 
            ++iterator;
    }
}

void Game::MoveAlienDown(int distance)
{
    for (auto& alien : aliens)
    {
        alien.pos.y += distance;
    }
}

void Game::CheckCollision()
{
    // spaceship laser

    for (auto& laser : spaceship.lasers)
    {
        auto iterator = aliens.begin();

        while (iterator != aliens.end())
        {
            if (CheckCollisionRecs (iterator -> getRect(), laser.getRect()))
            {
                iterator = aliens.erase(iterator);
                laser.active = false;
            } else 
                ++iterator;
        }

        for (auto& barrier : barriers)
        {
            auto iterator = barrier.pixels.begin();

            while (iterator != barrier.pixels.end())
            {
                if (CheckCollisionRecs (iterator -> getRect(), laser.getRect()))
                {
                    iterator = barrier.pixels.erase(iterator);
                    laser.active = false;
                } else
                    ++iterator;
            }
        }

        if (CheckCollisionRecs (mysteryship.getRect(), laser.getRect()))
        {
            mysteryship.alive = false;
            laser.active = false;
        }
    }

    // alien laser

    for (auto& laser : alienLaser)
    {
        if (CheckCollisionRecs (laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            lives--;

            if (lives == 0)
                GameOver();
        }


        for (auto& barrier : barriers)
        {
            auto iterator = barrier.pixels.begin();

            while (iterator != barrier.pixels.end())
            {
                if (CheckCollisionRecs (iterator -> getRect(), laser.getRect()))
                {
                    iterator = barrier.pixels.erase(iterator);
                    laser.active = false;
                } else
                    ++iterator;
            }
        }
    }

    // alien collision w barriers

    for (auto& alien : aliens)
    {
        for (auto& barrier : barriers)
        {
            auto iterator = barrier.pixels.begin();

            while (iterator != barrier.pixels.end())
            {
                if (CheckCollisionRecs (iterator -> getRect(), alien.getRect()))
                {
                    iterator = barrier.pixels.erase(iterator);
                } else 
                    iterator++;
            }
        }

        if (CheckCollisionRecs (alien.getRect(), spaceship.getRect()))
            GameOver();
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienLaser >= alienLaserInterval && !aliens.empty())
    {
        int randIndex = GetRandomValue (0, aliens.size() - 1);
        Alien& alien = aliens [randIndex];
    
        alienLaser.push_back (Laser({
        alien.pos.x + alien.alienImages[alien.type - 1].width / 2,
        alien.pos.y + alien.alienImages[alien.type - 1].height}, 6));
        
        timeLastAlienLaser = GetTime();
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

vector <Alien> Game::CreateAliens()
{
    vector <Alien> aliens;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 11; col++)
        {
            int typeAlien;

            if (row == 0)
                typeAlien = 3;
            else if (row == 1 || row == 2)
                typeAlien = 2;
            else 
                typeAlien = 1;

            float x = col * 55 + 75;
            float y = row * 55 + 110;
            aliens.push_back(Alien(typeAlien, {x, y}));
        }
    }

    return aliens;
}

void Game :: MoveAlien()
{
   for (auto& alien : aliens)
   {
        if (alien.pos.x + alien.alienImages[alien.type - 1].width > GetScreenWidth())
        {
            alienDirection = -1;
            MoveAlienDown(4);
        } else if (alien.pos. x < 0)
        {
            alienDirection = 1;
            MoveAlienDown(4);
        }

       alien.Update (alienDirection);
   }
}

void Game::GameOver()
{
    cout << "game over" << endl;
}
