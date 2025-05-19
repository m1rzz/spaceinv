using namespace std;
#pragma once
#include "spaceship.hpp"
#include "barrier.hpp"
#include "alien.hpp"

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
        void AlienShootLaser();
        void DeleteLasers();
        void MoveAlien();
        Spaceship spaceship;
        vector <Barrier> CreateBarrier();
        vector <Alien> CreateAliens();
        vector <Laser> alienLaser;
        vector <Barrier> barriers;
        vector <Alien> aliens;
        int alienDirection;
        float timeLastAlienLaser;
        constexpr static float alienLaserInterval = 0.35;
};