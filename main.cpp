#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include "barrier.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "space invaders");
    SetTargetFPS(60);

    Game game;
    Barrier barrier = Barrier({100, 100});

    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        barrier.Draw();

        EndDrawing();
    }

    cout << "lfikdhnf";
    CloseWindow();
    return 0;

}