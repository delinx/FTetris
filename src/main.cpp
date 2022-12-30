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

    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(120);

    GameLoop gameLoop;
    Block animationTest;
    animationTest.exist = true;
    animationTest.bucketPos = iXY(1, 1);
    gameLoop.bucket->set({ 5, 5 }, animationTest);
    gameLoop.bucket->set({ 5, 6 }, animationTest);

    while(!WindowShouldClose())
    {
        gameLoop.time += GetFrameTime();
        gameLoop.deltaTime = GetFrameTime();
        gameLoop.readKeyboard();

        gameLoop.tickLogic();
        gameLoop.tickMovement();

        BeginDrawing();
        ClearBackground(GRAY);
        DrawFPS(10, 10);
        DrawText("FTetris", 190, 200, 20, LIGHTGRAY);
        gameLoop.draw();
        EndDrawing();

        // debug toggle
        if(IsKeyReleased(KEY_TAB))
        {
            gameLoop.DEBUG = !gameLoop.DEBUG;
            Block tmp = gameLoop.bucket->get({ 5, 5 });
            tmp.updateTaregtPos({ 6, 5 });
            gameLoop.bucket->set({ 5, 5 }, tmp);
        }
    }

    CloseWindow();

    std::cout << "End" << std::endl;
    return 0;
}

#endif
