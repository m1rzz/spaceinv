#pragma once
#include "alien.hpp"
#include "barrier.hpp"
#include "spaceship.hpp"
#include "mysteryship.hpp"

using namespace std;

class Game
{

    public:

        Game();
        ~Game();
        void Draw();
        void Reset();
        void Update();
        void HandleInput();
        Music music;
        int lives;
        int score;
        int highscore;
        bool running;

    private:

        void MoveAlienDown (int distance);
        void AlienShootLaser();
        void CheckHighscore();
        void CheckCollision();
        void SaveHighscore (int highscore);
        int loadHighscore();
        void DeleteLasers();
        void MoveAlien();
        void GameOver();
        void InitGame();
        vector <Barrier> CreateBarrier();
        vector <Alien> CreateAliens();
        vector <Laser> alienLaser;
        vector <Barrier> barriers;
        vector <Alien> aliens;
        Spaceship spaceship;
        MysteryShip mysteryship;
        float timeLastAlienLaser;
        float mysteryShipSpawnInteval;
        float timeLastSpawn;
        int alienDirection;
        Sound explosionSound;
        Sound gameOverSound;
        constexpr static float alienLaserInterval = 0.35;
};