#pragma once
#include "alien.hpp"
#include "barrier.hpp"
#include "mysteryship.hpp"
#include "spaceship.hpp"

using namespace std;

class Game
{

    public:

        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool running;
        int highscore;
        int lives;
        int score;

    private:

        void MoveAlienDown (int distance);
        void AlienShootLaser();
        void CheckHighscore();
        void CheckCollision();
        void SaveHighscore (int highscore);
        void DeleteLasers();
        void MoveAlien();
        void GameOver();
        void InitGame();
        void Reset();
        MysteryShip mysteryship;
        Spaceship spaceship;
        vector <Barrier> CreateBarrier();
        vector <Alien> CreateAliens();
        vector <Laser> alienLaser;
        vector <Barrier> barriers;
        vector <Alien> aliens;
        int alienDirection;
        int loadHighscore();
        float timeLastSpawn;
        float timeLastAlienLaser;
        float mysteryShipSpawnInteval;
        constexpr static float alienLaserInterval = 0.35;
};