using namespace std;
#pragma once
#include "alien.hpp"
#include "barrier.hpp"
#include "mysteryship.hpp"
#include "spaceship.hpp"

class Game
{

    public:

        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();

    private:
        void MoveAlienDown(int distance);
        void CheckCollision();
        void AlienShootLaser();
        void DeleteLasers();
        void MoveAlien();
        Spaceship spaceship;
        MysteryShip mysteryship;
        vector <Barrier> CreateBarrier();
        vector <Alien> CreateAliens();
        vector <Laser> alienLaser;
        vector <Barrier> barriers;
        vector <Alien> aliens;
        int alienDirection;
        float timeLastAlienLaser;
        float mysteryShipSpawnInteval;
        float timeLastSpawn;
        constexpr static float alienLaserInterval = 0.35;
};