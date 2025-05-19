using namespace std;
#pragma once
#include "spaceship.hpp"
#include "barrier.hpp"

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
        vector <Barrier> CreateBarrier();
        Spaceship spaceship;
        vector <Barrier> barriers;
};