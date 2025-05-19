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
        void DeleteLasers();
        void MoveAlienDown(int distance);
        void MoveAlien();
        Spaceship spaceship;
        vector <Barrier> CreateBarrier();
        vector <Alien> CreateAliens();
        vector <Barrier> barriers;
        vector <Alien> aliens;
        int alienDirection;
};