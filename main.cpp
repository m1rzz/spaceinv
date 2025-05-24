#include <raylib.h>
#include <iostream>
#include "game.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int windowWidth = 750;
    int windowHeight = 700;
    int offset = 50;

    InitWindow (windowWidth + offset, windowHeight + (offset * 2), "space invaders");
    SetTargetFPS (60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground (grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 2, yellow);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;

}