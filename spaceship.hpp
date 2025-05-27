#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

using namespace std;

class Spaceship
{
    public:

        Spaceship();
        ~Spaceship();
        vector <Laser> lasers;
        Rectangle getRect();
        void MoveRight();
        void FireLaser();
        void MoveLeft();
        void Reset();
        void Draw();
 
    private:

        double lastShotTime;
        Sound laserSound;
        Texture2D image;
        Vector2 pos;

};