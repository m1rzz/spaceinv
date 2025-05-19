#pragma once
#include <raylib.h>

class Alien
{
    public:
        Alien (int type, Vector2 pos);
        static Texture2D alienImages [3];
        static void UnloadImages();
        int GetType();
        void Update();
        void Draw();
        Vector2 pos;
        int type;
    private:
};