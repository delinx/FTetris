#include "gameLoop.hpp"
#include "raylib.h"
#include "types/grid.hpp"
#include "types/types.hpp"

#ifdef UNIT_TEST
#include "uTest.cpp"
#else

#include <iostream>

int main(int argc, char *argv[])
{

    int screenWidth = 500;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(200);

    GameLoop gameLoop;

    Block block1;
    block1.exist = true;
    block1.bucketPos = { 0, 19 };
    block1.forceUpdateVisualPos();
    block1.BaseColor = RED;
    gameLoop.bucket->set({ 0, 19 }, block1);
    block1.bucketPos = { 1, 19 };
    gameLoop.bucket->set({ 1, 19 }, block1);
    block1.bucketPos = { 2, 19 };
    gameLoop.bucket->set({ 2, 19 }, block1);
    block1.bucketPos = { 3, 19 };
    gameLoop.bucket->set({ 3, 19 }, block1);
    block1.bucketPos = { 4, 19 };
    gameLoop.bucket->set({ 4, 19 }, block1);
    block1.bucketPos = { 6, 19 };
    gameLoop.bucket->set({ 6, 19 }, block1);
    block1.bucketPos = { 7, 19 };
    gameLoop.bucket->set({ 7, 19 }, block1);
    block1.bucketPos = { 8, 19 };
    gameLoop.bucket->set({ 8, 19 }, block1);
    block1.bucketPos = { 9, 19 };
    gameLoop.bucket->set({ 9, 19 }, block1);

    while(!WindowShouldClose())
    {
        gameLoop.DEBUG = IsKeyReleased(KEY_TAB) ? !gameLoop.DEBUG : gameLoop.DEBUG;

        gameLoop.time += GetFrameTime();
        gameLoop.deltaTime = GetFrameTime();
        gameLoop.readKeyboard();

        gameLoop.tickLogic();
        gameLoop.tickMovement();

        BeginDrawing();
        ClearBackground(BLACK);
        gameLoop.drawBackground();
        gameLoop.draw();

        // draw hints and controls
        DrawText("* SCORE *\n [ ] +50 \n +10xROW\n A +400\n B +800 \n C +1200", 330, 190, 20, LIGHTGRAY);
        DrawText("* CONTROLS *\n[<] [>] \n - MOVE\nUP/DOWN\n - ROTATION\n[SPACE]\n - 4X SPEED", 330, 390, 20, GRAY);


        if(gameLoop.lost)
        {
            DrawRectangle(0, 0, 500, 600, Color { 0, 0, 0, 100 });
            DrawText("Game Over", 90, 200, 60, RED);
            DrawText("Press [ENTER] to play again", 30, 300, 28, WHITE);
            if(IsKeyReleased(KEY_ENTER))
            {
                gameLoop.newGame();
            }
        }

        gameLoop.tickScore();
        gameLoop.drawScore();

        if(gameLoop.DEBUG)
        {
            DrawFPS(10, 10);
            std::string strtmp = "blocksStillAnimating:" + std::to_string(gameLoop.blocksStillAnimating);
            DrawText(strtmp.c_str(), 10, 70, 20, RED);
            if(gameLoop.inAnimationFreeze)
            {
                DrawText("inAnimationFreeze", 10, 30, 20, RED);
            }
        }
        // debug toggle
        EndDrawing();
    }

    CloseWindow();

    std::cout << "End" << std::endl;
    return 0;
}

#endif
