using namespace std;
#include <fstream>
#include <iostream>
#include "game.hpp"

using namespace std;

Game :: Game()
{
    //konstruktur
    InitGame();
}

Game :: ~Game()
{
    // destruktur
    Alien :: UnloadImages();
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
    // printira vsichki obekti 
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
    // razpoznava input ot klaviaturata na usera 
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

    // iztriva lazeri za da free upne pamet 
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
    // dviji izvunzemnite nadolu
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
                if (iterator -> type == 1)
                    score += 100;
                else if (iterator -> type == 2)
                    score += 200;
                else if (iterator -> type == 3)
                    score += 300;
                CheckHighscore();

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
            score += 500;

            CheckHighscore();
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
    // creates an instance of output stream class
    ofstream highscoreFile ("highscore.txt");

    if (highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    } else 
        cerr << "Failed to save highscore" << endl;

        // cerr - standard error stream
        // similar to cout
        // displays error msgs immediately
}

int Game :: loadHighscore()
{
    int loadedHS = 0;

    // ifstream - input file stream
    // reads txt/binary files
    // extracts data
    // checks file states 
    ifstream highscoreFile ("highscore.txt");
    // the highscoreFile object reads from highscore.txt

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
    // interval ot vreme prez koito mogat da strelqt izvunzemnite
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

    // suzdava 4 barieri na simetrichni intervali 
    int barrierWidth = Barrier :: grid[0].size() * 3;
    float gaps = (GetScreenWidth() - (4 * barrierWidth)) / 3;

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
    // printira razlichnite vidove izvunzemni sprqmo reda na koito se namirat
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

    // dviji redovete s izvunzemni po x axis
    // namestva gi v prozoreca na igrata, za da ne izlizat izvun scope-a

   for (auto& alien : aliens)
   {
        if (alien.pos.x + alien.alienImages[alien.type - 1].width
        > GetScreenWidth() - 25)
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
    // prekratqva igrata

    running = false;
}

void Game :: InitGame()
{

    // zadava purvonachalni stoinosti pri puskane na igrata
    barriers = CreateBarrier();
    aliens = CreateAliens();
    running = true;
    lives = 3;
    score = 0;
    highscore = loadHighscore();
    alienDirection = 1;
    timeLastAlienLaser = 0.0;
    timeLastSpawn = 0.0f;
    mysteryShipSpawnInteval = GetRandomValue (10, 20);
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
    // resetva vsichki obekti pri restartirane na igrata

    spaceship.Reset();
    aliens.clear();
    alienLaser.clear();
    barriers.clear();
}