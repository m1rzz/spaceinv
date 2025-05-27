#pragma once
#include <vector>
#include "pixel.hpp"

using namespace std;

class Barrier
{
    public:

        Barrier (Vector2 pos);
        void Draw();
        Vector2 pos;
        vector <Pixel> pixels;
        static vector <vector <int>> grid;

    private:
};