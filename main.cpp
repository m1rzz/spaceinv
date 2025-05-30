#include <raylib.h>
#include <string>
#include "game.hpp"

using namespace std;

string LeadingZeroes (int num, int width)
{
    string numTxt = to_string (num);
    int zeroes = width - numTxt.length();

    return numTxt = string (zeroes, '0') + numTxt;
}

int main()
{
    int windowWidth = 800;
    int windowHeight = 800;
    InitWindow (windowWidth, windowHeight, "Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx ("Font/monogram.ttf", 64, 0, 0);
    Texture2D heartImage = LoadTexture ("Graphics/heart.png");

    Game game;
 
    float blinkTimer = 0;
    bool showTxt = true;
    
    Color grey = {29, 29, 27, 255};
    Color red = {255, 60, 0, 255};
    Color yellow = {243, 216, 63, 255};
    
    SetTargetFPS (60);

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream (game.music);
        game.HandleInput();
        game.Update();

        // makes blinking text
        blinkTimer += GetFrameTime();
        if (blinkTimer >= 0.7f)
        {
            showTxt = !showTxt;
            blinkTimer = 0;
        }

        BeginDrawing();
        ClearBackground (grey);

        DrawRectangleRoundedLinesEx ({10, 10, 780, 780}, 0.20f, 20, 2, yellow);
        DrawLineEx ({10, 720}, {790, 720}, 2, yellow);
        
        if (game.running)
            DrawTextEx (font, "LEVEL 01", {570, 735}, 34, 2, yellow);
        else if (game.lives == 0 && showTxt)
        {
            DrawTextEx (font, "PRESS ENTER TO RESTART", {350, 735}, 34, 2, yellow);
            DrawTextEx (font, "GAME OVER", {75, 735}, 34, 2, red);

        } else if (game.alienLives == 0 && showTxt)
        {
            DrawTextEx (font, "VICTORY", {280, 325}, 70, 2, yellow);
            DrawTextEx (font, "PRESS ENTER TO RESTART", {350, 735}, 34, 2, yellow);
        }

        float x = 50.0;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV (heartImage, {x, 730}, WHITE);
            x += 50;
        }

        string scoreTxt = LeadingZeroes (game.score, 5);
        DrawTextEx (font, "SCORE", {75, 15}, 34, 2, yellow);
        DrawTextEx (font, scoreTxt.c_str(), {75, 40}, 34, 2, yellow);

        DrawTextEx (font, "HIGH-SCORE", {555, 15}, 34, 2, yellow);
        string highscoreTxt = LeadingZeroes (game.highscore, 5);
        DrawTextEx (font, highscoreTxt.c_str(), {645, 40}, 34, 2, yellow);
        
        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;

}