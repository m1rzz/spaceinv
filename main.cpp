#include <raylib.h>
#include <iostream>
#include "game.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int windowWidth = 800;
    int windowHeight = 800;

    InitWindow (windowWidth, windowHeight, "Space Invaders");
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