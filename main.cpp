#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include "laser.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "space invaders");
    SetTargetFPS(60);

    Game game;
    Laser laser = Laser({100, 100}, -7);

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        laser.Update();

        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        laser.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;

}