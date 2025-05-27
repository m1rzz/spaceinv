#include <fstream>
#include <iostream>
#include <raylib.h>
#include "game.hpp"
#include "alien.hpp"

using namespace std;

Game :: Game()
{
    music = LoadMusicStream ("Sounds/bgmusic.wav");
    victoryMusic = LoadSound ("Sounds/winmusic.wav");
    explosionSound = LoadSound ("Sounds/explosion.ogg");
    gameOverSound = LoadSound ("Sounds/gameover.wav");
    
    SetMusicVolume (music, 0.2f);
    SetSoundVolume (victoryMusic, 0.3f);
    SetSoundVolume (explosionSound, 0.4f);
    SetSoundVolume (gameOverSound, 0.4f);
    
    InitGame();
}

Game :: ~Game()
{
    Alien :: UnloadImages();

    UnloadSound (explosionSound);
}

void Game :: Update()
{
    if (running)
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

    } else 
    {
        if (IsKeyDown (KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
}

void Game :: Draw()
{
    spaceship.Draw();

    for (auto& laser : spaceship.lasers)
        laser.Draw();

    for (auto& barrier : barriers)
        barrier.Draw();

    for (auto& alien : aliens)
        alien.Draw();

    for (auto& laser : alienLaser)
        laser.Draw();

    mysteryship.Draw();
}

void Game :: HandleInput()
{
    if (running)
    {
        if (IsKeyDown (KEY_LEFT)) 
            spaceship.MoveLeft();
        else if (IsKeyDown (KEY_RIGHT)) 
            spaceship.MoveRight();
        else if (IsKeyDown (KEY_SPACE))
            spaceship.FireLaser();
    }
}

void Game :: DeleteLasers()
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

void Game :: MoveAlienDown (int distance)
{
    for (auto& alien : aliens)
        alien.pos.y += distance;
}

void Game :: CheckCollision()
{
    // spaceship laser
    for (auto& laser : spaceship.lasers)
    {
        auto iterator = aliens.begin();

        while (iterator != aliens.end())
        {
            if (CheckCollisionRecs (iterator -> getRect(), laser.getRect()))
            {
                PlaySound (explosionSound);

                if (iterator -> type == 1)
                    score += 100;
                else if (iterator -> type == 2)
                    score += 200;
                else if (iterator -> type == 3)
                    score += 300;
                CheckHighscore();

                alienLives--;
                iterator = aliens.erase(iterator);
                laser.active = false;
                Victory();

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
            score += 500;

            CheckHighscore();
            PlaySound (explosionSound);
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
            {
                GameOver();
            }
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
                    iterator = barrier.pixels.erase(iterator);
                else 
                    iterator++;
            }
        }

        if (CheckCollisionRecs (alien.getRect(), spaceship.getRect()))
            GameOver();
    }
}

void Game :: SaveHighscore (int highscore)
{
    ofstream highscoreFile ("highscore.txt");

    if (highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    } else 
        cerr << "Failed to save highscore" << endl;
}

int Game :: loadHighscore()
{
    int loadedHS = 0;
    ifstream highscoreFile ("highscore.txt");

    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHS;
        highscoreFile.close();
    } else
        cerr << "Failed to load highscore" << endl;

    return loadedHS;
}

void Game :: AlienShootLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienLaser >= alienLaserInterval && !aliens.empty())
    {
        int randIndex = GetRandomValue (0, aliens.size() - 1);
        Alien& alien = aliens[randIndex];
    
        alienLaser.push_back (Laser({
        alien.pos.x + alien.alienImages[alien.type - 1].width / 2,
        alien.pos.y + alien.alienImages[alien.type - 1].height}, 6));
        
        timeLastAlienLaser = GetTime();
    }

}

vector <Barrier> Game :: CreateBarrier()
{
    int barrierWidth = Barrier :: grid[0].size() * 3;
    float gaps = (GetScreenWidth() - 4 * barrierWidth) / 3;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = i * gaps + (barrierWidth * 1.5f);
        barriers.push_back (Barrier ({offsetX, 
        float (GetScreenHeight() - 100)}));
    }
    
    return barriers;
}

vector <Alien> Game :: CreateAliens()
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
        if (alien.pos.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            alienDirection = -1;
            MoveAlienDown(4);
        } if (alien.pos.x < 25)
        {
            alienDirection = 1;
            MoveAlienDown(4);
        }

       alien.Update (alienDirection);
   }
}

void Game :: GameOver()
{
    PlaySound (gameOverSound);
    StopMusicStream (music);
    running = false;
}

void Game :: InitGame()
{
    PlayMusicStream (music);
    highscore = loadHighscore();
    barriers = CreateBarrier();
    aliens = CreateAliens();
    alienLives = 55;
    alienDirection = 1;
    running = true;
    lives = 3;
    score = 0;
    timeLastSpawn = 0.0f;
    timeLastAlienLaser = 0.0;
    mysteryShipSpawnInteval = GetRandomValue (10, 20);
}

bool Game :: Victory()
{
    if (alienLives <= 0)
    {
        PlaySound (victoryMusic);
        StopMusicStream (music);
        
        running = false;
    }
    
    return true;
}

void Game :: CheckHighscore()
{
    if (score > highscore)
    {
        highscore = score;
        SaveHighscore (highscore);
    }
}

void Game :: Reset()
{
    spaceship.Reset();
    alienLaser.clear();
    barriers.clear();
    aliens.clear();
}