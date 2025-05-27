#pragma once
#include <raylib.h>

class Alien
{
    public:

        Alien (int type, Vector2 pos);
        int GetType();
        int type;
        Vector2 pos;
        Rectangle getRect();
        static Texture2D alienImages[3];
        static void UnloadImages();
        void Update (int direction);
        void Draw();
        
    private:
};