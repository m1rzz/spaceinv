#pragma once
#include <raylib.h>

class Alien
{
    public:

        Alien (int type, Vector2 pos);
        Rectangle getRect();
        Vector2 pos;
        static Texture2D alienImages[3];
        static void UnloadImages();
        void Update (int direction);
        int GetType();
        void Draw();
        int type;
        
    private:
};