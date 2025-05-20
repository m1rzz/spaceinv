using namespace std;
#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship
{
    public:

        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        Rectangle getRect();
        vector <Laser> lasers;
 
    private:
    
        double lastShotTime;
        Texture2D image;
        Vector2 pos;

};