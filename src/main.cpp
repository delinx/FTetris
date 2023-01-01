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
        ClearBackground(GRAY);
        DrawText("FTetris", 190, 200, 20, LIGHTGRAY);
        gameLoop.drawBackground();
        gameLoop.draw();

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
