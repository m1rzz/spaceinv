#include <raylib.h>
#include <iostream>
#include "game.hpp"

int main()
{
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    Color red = {255, 60, 0, 255};

    int windowWidth = 800;
    int windowHeight = 800;

    InitWindow (windowWidth, windowHeight, "Space Invaders");
    Font font = LoadFontEx ("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture ("Graphics/heart.png");

    SetTargetFPS (60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();
        ClearBackground (grey);

        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.20f, 20, 2, yellow);
        DrawLineEx ({10, 720}, {790, 720}, 2, yellow);
        
        if (game.running)
            DrawTextEx (font, "LEVEL 01", {570, 735}, 34, 2, yellow);
        else 
            DrawTextEx (font, "GAME OVER", {570, 735}, 34, 2, red);

        float x = 50.0;
        for (int i =0; i < game.lives; i++)
        {
            DrawTextureV (spaceshipImage, {x, 730}, WHITE);
            x += 50;
        }

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;

}