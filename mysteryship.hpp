#pragma once
#include <raylib.h>

class MysteryShip
{
    public:

        MysteryShip();
        ~MysteryShip();
        Rectangle getRect();
        void Update();
        void Spawn();
        void Draw();
        bool alive;
        
    private:

        Texture2D image;
        Vector2 pos;
        int speed;
};